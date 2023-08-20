#include <Device/UsbDBulkInterface.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stm32f7xx_hal.h>
//#include <main.h>
#include <stm32f7xx_ll_rcc.h>
#include <LFramework/Debug.h>
#include <LFramework/IO/Terminal/TerminalAnsi.h>
#include <LFramework/Threading/Thread.h>
#include <cstring>
//#include <usart.h>
//#include <tim.h>

#include <Usb/Usb.h>

#include <MicroNetwork/Device/Node.h>
#include <MicroNetwork/Device/UsbTransmitter.h>
#include <MicroNetwork/Device/TaskManager.h>
#include <Tasks/MemoryAccess.h>
#include <type_traits>

#include "PinMap.h"

using namespace LFramework;
using namespace MicroNetwork;


namespace LFramework {
	OutputStream<char>& operator <<(OutputStream<char>& stream, const LFramework::InterfaceID& id){
		
		return stream << HexFormat<std::uint32_t, false, 8>(id.data1) << "-" 
			<< HexFormat<std::uint16_t, false, 4>(id.data2_3 & 0xffff) << "-"
			<< HexFormat<std::uint16_t, false, 4>((id.data2_3 & 0xffff0000) >> 16) << "-"

			<< HexFormat<std::uint16_t, false, 2>(id.data4_0 & 0xff) << HexFormat<std::uint16_t, false, 2>((id.data4_0 & 0xff00) >> 8) << "-"
			<< HexFormat<std::uint16_t, false, 2>((id.data4_0 & 0xff0000) >> 16) << HexFormat<std::uint16_t, false, 2>((id.data4_0 & 0xff000000) >> 24)
			
			<< HexFormat<std::uint16_t, false, 2>((id.data4_1 & 0xff) >> 0)
			<< HexFormat<std::uint16_t, false, 2>((id.data4_1 & 0xff00) >> 8)
			<< HexFormat<std::uint16_t, false, 2>((id.data4_1 & 0xff0000) >> 16)
			<< HexFormat<std::uint16_t, false, 2>((id.data4_1 & 0xff000000) >> 24);
	}
}


class TestTaskManager : public Device::TaskManager {
public:
	struct TaskRecord{
		typedef LFramework::ComPtr<Device::ITask>(*taskConstructor)();
		LFramework::Guid guid;
		taskConstructor constructor;
		TaskRecord* next;
	};

	template<typename Task, typename IoDescriptor>
	void addTask() {
		static TaskRecord record = {IoDescriptor::ID(), [](){ return LFramework::ComPtr<Device::ITask>::create<Task>(); }, reinterpret_cast<TaskRecord*>(-1)};

		if(_tasks == nullptr){
			_tasks = &record;
			record.next = nullptr;
		}else{
			if(record.next == reinterpret_cast<TaskRecord*>(-1)){
				_tasks->next = &record;
				record.next = nullptr;
			}
		}
	}

	std::size_t getTasksCount() {
		std::size_t result = 0;
		TaskRecord* task = _tasks;
		while(task != nullptr){
			++result;
			task = task->next;
		}
		return result;
	}
	bool getTaskId(std::size_t id, LFramework::Guid& result) {
		TaskRecord* task = _tasks;
		for(std::size_t i = 0; i < id; ++i){
			if(task != nullptr){
				task = task->next;
			}else{
				break;
			}
		}

		if(task != nullptr){
			result = task->guid;
			return true;
		}

		return false;
	}

	LFramework::ComPtr<Device::ITask> createTask(LFramework::Guid& taskId) {
		TaskRecord* task = _tasks;
		while(task != nullptr){
			if(task->guid == taskId){
				return task->constructor();
			}
			task = task->next;
		}
		return nullptr;
	}
	void deleteTask(Device::Task* task) {
		delete task;
	}
private:
	TaskRecord* _tasks = nullptr;
};



void mainThread(void * argument){
	Terminal::out << Terminal::Ansi::Cursor::MoveHome() << Terminal::Ansi::Viewport::ClearScreen();
	Debug::Log() << "Hello!";

	Usb* usb = new Usb();
	Device::UsbTransmitter* usbTransmitter = new Device::UsbTransmitter(usb->usbInterface);


	//{9ac2fee8-ecd0-461d-9906-9bc28d01b9a2}
	Debug::Log() << "Reference interface ID: 9ac2fee8-ecd0-461d-9906-9bc28d01b9a2";
	Debug::Log() << "Real interface ID     : " << MicroNetwork::Task::MemoryAccess::IStreamIoStreamDescriptor::ID();

	auto taskManager = new TestTaskManager();
	taskManager->addTask<MemoryAccess, MicroNetwork::Task::MemoryAccess::IStreamIoStreamDescriptor>();

	
	Debug::Log() << "Task count: " << taskManager->getTasksCount();
	for(std::size_t i = 0; i < taskManager->getTasksCount(); ++i){
		LFramework::InterfaceID id;
		if(!taskManager->getTaskId(i, id)){
			Debug::Log() << "taskManager error: failed to get task ID";
		}else{
			Debug::Log() << "TaskNumber: " << i << " Task GUID: " << id;
		}
	}

	Device::Node* node = new Device::Node(taskManager);


	usbTransmitter->bind(node);
	node->bind(usbTransmitter);


	Threading::Thread nodeThread("node", 1024, Threading::ThreadPriority::Normal, [node](){
		node->start();
		node->process();
	});

	lfDebug() << "Starting USB transmitter";
	usbTransmitter->start();
	lfDebug() << "USB transmitter started";

	for(;;){
		Threading::ThisThread::sleepForMs(100);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}

}

extern "C" void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName){
	Debug::Log() << "Stack overflow in task " << (const char*)pcTaskName;
	for(;;);
}
extern "C" void vApplicationMallocFailedHook(void){
	Debug::Log() << "Malloc failed";
	for(;;);
}
