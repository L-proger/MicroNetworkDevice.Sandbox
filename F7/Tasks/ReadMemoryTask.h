#pragma once

#include <LFramework/Debug.h>
#include <MicroNetwork/Device/Task.h>
#include <LFramework/Threading/Thread.h>

class ReadMemoryTask : public MicroNetwork::Device::Task {
public:
	LFramework::Result packet(MicroNetwork::Common::PacketHeader header, const void* data) override {
		lfDebug() << "Task packet receive: " << header.id << ":" << header.size;
		return LFramework::Result::Ok;
	}

	LFramework::Result run(LFramework::ComPtr<MicroNetwork::Device::ITaskContext> context) {
		lfDebug() << "ReadMemoryTask enter";
		MicroNetwork::Common::MaxPacket packet;
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
			LFramework::Threading::ThisThread::sleepForMs(1);
		}
		lfDebug() << "ReadMemoryTask exit";
		return LFramework::Result::Ok;
	}
};
