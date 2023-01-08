#pragma once
//imported type: std::uint8_t from module: cstdint
//imported type: LFramework::IUnknown from module: LFramework/COM/ComObject.h
//imported type: void from module: LanguagePrimitive
#include <LFramework/COM/ComObject.h>
#include <cstdint>
namespace MicroNetwork::Common{
    struct PacketHeader{
        std::uint8_t id;
        std::uint8_t size;
    }; //PacketHeader
}
namespace MicroNetwork::Common{
    class IDataReceiver;
} //MicroNetwork::Common
namespace LFramework{
    //Interface ABI
    template<>
    struct InterfaceAbi<MicroNetwork::Common::IDataReceiver> : public InterfaceAbi<LFramework::IUnknown>{
        using Base = InterfaceAbi<LFramework::IUnknown>;
        //{7d055626-dae1-4cc7-81d0-ed813d57bd73}
        static constexpr InterfaceID ID() { return { 0x7d055626, 0x4cc7dae1, 0x81edd081, 0x73bd573d }; }
        virtual Result LFRAMEWORK_COM_CALL packet(MicroNetwork::Common::PacketHeader header, const void* data) = 0;
    private:
        ~InterfaceAbi() = delete;
    }; //IDataReceiver
    //Interface Remap
    template<class TImplementer>
    struct InterfaceRemap<MicroNetwork::Common::IDataReceiver, TImplementer> : public InterfaceRemap<LFramework::IUnknown, TImplementer>{
        virtual Result LFRAMEWORK_COM_CALL packet(MicroNetwork::Common::PacketHeader header, const void* data){
            Result comCallResult_ = this->implementer()->packet(header, data);
            return comCallResult_;
        }
    };
    //Interface Wrapper
    template<>
    class InterfaceWrapper<MicroNetwork::Common::IDataReceiver> : public InterfaceWrapper<LFramework::IUnknown> {
    public:
        Result packet(MicroNetwork::Common::PacketHeader header, const void* data){
            return reinterpret_cast<InterfaceAbi<MicroNetwork::Common::IDataReceiver>*>(_abi)->packet(header, data);
        } //packet
    };
}

