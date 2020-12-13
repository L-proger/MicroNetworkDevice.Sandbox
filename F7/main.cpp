#include <Device/UsbDBulkInterface.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stm32f7xx_hal.h>
#include <main.h>

#include <LFramework/Debug.h>
#include <LFramework/IO/Terminal/TerminalAnsi.h>
#include <LFramework/Threading/Thread.h>
#include <cstring>
#include <usart.h>
#include <tim.h>

#include <Usb/Usb.h>

#include <MicroNetwork/Device/Node.h>
#include <MicroNetwork/Device/UsbTransmitter.h>
#include <MicroNetwork/Device/TaskManager.h>
#include <MicroNetwork/Device/Task.h>

using namespace LFramework;
using namespace MicroNetwork;

class TestTask : public Device::Task {
public:
	LFramework::Result packet(Common::PacketHeader header, const void* data) {
		lfDebug() << "Task packet receive: " << header.id << ":" << header.size;
		return LFramework::Result::Ok;
	}

	LFramework::Result run(LFramework::ComPtr<Device::ITaskContext> context) {
		lfDebug() << "Task started";
		Common::MaxPacket packet;
		packet.header.id = 7;
		packet.header.size = 3;
		packet.payload[0] = 0;
		packet.payload[1] = 0;
		packet.payload[2] = 0;
		while(true){
			bool exitRequested = false;
			context->isExitRequested(exitRequested);
			if(exitRequested){
				break;
			}

			context->readPackets();
			auto writeResult = context->packet(packet.header, packet.payload.data());
			//lfDebug() << "Task packet write: " << (writeResult ? "OK" : "FAIL");
			Threading::ThisThread::sleepForMs(10);
		}
		lfDebug() << "Task stopped";
		return LFramework::Result::Ok;
	}
};


class TestTaskManager : public Device::TaskManager {
public:
	std::size_t getTasksCount() {
		return 1;
	}
	bool getTaskId(std::size_t id, LFramework::Guid& result) {
		result = { 0x292464d1, 0xaf7a, 0x4e01, { 0x98, 0xc6, 0x27, 0x30, 0x48, 0x3d, 0x36, 0x6f } };
		return id == 0;
	}

	LFramework::ComPtr<Device::ITask> createTask() {
		return LFramework::ComPtr<Device::ITask>::create<TestTask>();
	}
	void deleteTask(Device::Task* task) {
		delete task;
	}
};



extern"C" void StartDefaultTask(void const * argument){
	Terminal::out << Terminal::Ansi::Cursor::MoveHome() << Terminal::Ansi::Viewport::ClearScreen();
	Debug::Log() << "Hello!";

	Usb* usb = new Usb();
	Device::UsbTransmitter* usbTransmitter = new Device::UsbTransmitter(usb->usbInterface);


	auto taskManager = new TestTaskManager();

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

extern "C" void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName){
	Debug::Log() << "Stack overflow in task " << (const char*)pcTaskName;
	for(;;);
}
extern "C" void vApplicationMallocFailedHook(void){
	Debug::Log() << "Malloc failed";
	for(;;);
}
