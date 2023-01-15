#pragma once
#include <LFramework/COM/ComObject.h>
#include <MicroNetwork.Task.MemoryAccess.h>
#include <MicroNetwork.Task.MemoryAccess.IHostToDevice.Serializer.In.h>
#include <MicroNetwork.Task.MemoryAccess.IDeviceToHost.Serializer.Out.h>
namespace MicroNetwork::Task::MemoryAccess{
    struct IStreamIoStreamDescriptor{
        //{9ac2fee8-ecd0-461d-9906-9bc28d01b9a2}
        static constexpr LFramework::InterfaceID ID() { return { 0x9ac2fee8, 0x461decd0, 0xc29b0699, 0xa2b9018d }; }
        using InInterface = MicroNetwork::Task::MemoryAccess::IHostToDevice;
        using InInterfaceSerializer = MicroNetwork::Task::MemoryAccess::IHostToDeviceSerializerIn;
        using OutInterface = MicroNetwork::Task::MemoryAccess::IDeviceToHost;
        using OutInterfaceSerializer = MicroNetwork::Task::MemoryAccess::IDeviceToHostSerializerOut;
    };
}

