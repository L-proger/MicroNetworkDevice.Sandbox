#pragma once
#include <LFramework/COM/ComObject.h>
#include <MicroNetwork.Common.h>
#include <MicroNetwork.Task.MemoryAccess.h>
namespace MicroNetwork::Task::MemoryAccess{
    class IDeviceToHostSerializerOut : public LFramework::ComImplement<IDeviceToHostSerializerOut, LFramework::ComObject, MicroNetwork::Task::MemoryAccess::IDeviceToHost>{
    public:
        IDeviceToHostSerializerOut(LFramework::ComPtr<MicroNetwork::Common::IDataReceiver> next) : _next(next){
        }
        LFramework::Result readResponse(MicroNetwork::Task::MemoryAccess::MemoryBlob response){
            //PacketID: 0
            MicroNetwork::Common::PacketHeader header;
            header.id = 0;
            header.size = sizeof(MicroNetwork::Task::MemoryAccess::MemoryBlob);
            return _next->packet(header, &response);
        }
        LFramework::Result writeResponse(bool success){
            //PacketID: 1
            MicroNetwork::Common::PacketHeader header;
            header.id = 1;
            header.size = sizeof(bool);
            return _next->packet(header, &success);
        }
    public:
        LFramework::ComPtr<MicroNetwork::Common::IDataReceiver> _next;
    };
}

