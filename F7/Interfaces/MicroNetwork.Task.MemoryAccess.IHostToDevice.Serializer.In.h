#pragma once
#include <LFramework/COM/ComObject.h>
#include <MicroNetwork.Common.h>
#include <MicroNetwork.Task.MemoryAccess.h>
namespace MicroNetwork::Task::MemoryAccess{
    class IHostToDeviceSerializerIn : public LFramework::ComImplement<IHostToDeviceSerializerIn, LFramework::ComObject, MicroNetwork::Common::IDataReceiver>{
    public:
        IHostToDeviceSerializerIn(LFramework::ComPtr<MicroNetwork::Task::MemoryAccess::IHostToDevice> next) : _next(next){
        }
        LFramework::Result packet(MicroNetwork::Common::PacketHeader header, const void* data){
            switch (header.id){
            case 0:
                _next->read(*(reinterpret_cast<const MicroNetwork::Task::MemoryAccess::MemoryRegion*>(data)));
                return LFramework::Result::Ok;
            case 1:
                _next->write(*(reinterpret_cast<const MicroNetwork::Task::MemoryAccess::MemoryBlob*>(data)));
                return LFramework::Result::Ok;
            default:
                return LFramework::Result::InvalidArg;
            }
        }
    public:
        LFramework::ComPtr<MicroNetwork::Task::MemoryAccess::IHostToDevice> _next;
    };
}

