#pragma once
#include <LFramework/Debug.h>
#include <MicroNetwork/Device/Task.h>
#include <LFramework/Threading/Thread.h>
#include <MicroNetwork.Task.MemoryAccess.IHostToDevice.Serializer.In.h>
#include <MicroNetwork.Task.MemoryAccess.IDeviceToHost.Serializer.Out.h>
#include <MicroNetwork.Task.MemoryAccess.IStream.IoStreamDescriptor.h>
class MemoryAccess : public LFramework::ComImplement<MemoryAccess, MicroNetwork::Device::Task, MicroNetwork::Task::MemoryAccess::IStreamIoStreamDescriptor::InInterface> {
public:
	LFramework::ComPtr<MicroNetwork::Common::IDataReceiver> _inStream;
	MemoryAccess() {
		_inStream = LFramework::ComPtr<MicroNetwork::Common::IDataReceiver>
			::create<MicroNetwork::Task::MemoryAccess::IStreamIoStreamDescriptor::InInterfaceSerializer>(queryInterface<MicroNetwork::Task::MemoryAccess::IHostToDevice>());
	}
	LFramework::Result packet(MicroNetwork::Common::PacketHeader header, const void* data) override {
		return _inStream->packet(header, data);
	}
	LFramework::Result read(MicroNetwork::Task::MemoryAccess::MemoryRegion request) {
		lfDebug() << "MemoryAccess: read: address = " << request.address << " size = " << request.size;
		return LFramework::Result::Ok;
	}
	LFramework::Result write(MicroNetwork::Task::MemoryAccess::MemoryBlob request) {
		lfDebug() << "MemoryAccess: write: address = " << request.header.address << " size = " << request.header.size;
		return LFramework::Result::Ok;
	}
	LFramework::Result run(LFramework::ComPtr<MicroNetwork::Device::ITaskContext> context) {
		auto outStream = LFramework::ComPtr<MicroNetwork::Task::MemoryAccess::IStreamIoStreamDescriptor::OutInterface>
			::create<MicroNetwork::Task::MemoryAccess::IStreamIoStreamDescriptor::OutInterfaceSerializer>(context->queryInterface<MicroNetwork::Common::IDataReceiver>());

		lfDebug() << "MemoryAccess enter";

		MicroNetwork::Task::MemoryAccess::MemoryBlob response;
		response.header.address = 111;
		response.header.size = 64;

		std::uint8_t* pData = reinterpret_cast<std::uint8_t*>(&response.data);
		for(std::uint32_t i = 0; i < response.header.size; ++i){
			pData[i] = static_cast<std::uint8_t>(i);
		}
		
		while(true){
			bool exitRequested = false;
			context->isExitRequested(exitRequested);
			if(exitRequested){
				break;
			}

			context->readPackets();
			outStream->readResponse(response);

			//lfDebug() << "Task packet write: " << (writeResult ? "OK" : "FAIL");
			LFramework::Threading::ThisThread::sleepForMs(1);
		}
		lfDebug() << "MemoryAccess exit";
		return LFramework::Result::Ok;
	}
};
