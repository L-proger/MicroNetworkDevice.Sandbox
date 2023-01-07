#pragma once
//imported type: IDataReceiver from module: MicroNetwork.Common
//imported type: void from module: LanguagePrimitive
//imported type: bool from module: LanguagePrimitive
//imported type: ITaskContext from module: MicroNetwork.Device
#include <MicroNetwork.Common.h>
#include <MicroNetwork.Device.h>
namespace MicroNetwork::Device{
    class ITaskContext;
} //MicroNetwork::Device
namespace LFramework{
    //Interface ABI
    template<>
    struct InterfaceAbi<MicroNetwork::Device::ITaskContext> : public InterfaceAbi<MicroNetwork::Common::IDataReceiver>{
        using Base = InterfaceAbi<MicroNetwork::Common::IDataReceiver>;
        //{fcff1d12-3da5-49d9-a860-a61d279486bb}
        static constexpr InterfaceID ID() { return { 0xfcff1d12, 0x3da5, 0x49d9, { 0xa8, 0x60, 0xa6, 0x1d, 0x27, 0x94, 0x86, 0xbb } }; }
        virtual Result LFRAMEWORK_COM_CALL readPackets() = 0;
        virtual Result LFRAMEWORK_COM_CALL isExitRequested(bool& result) = 0;
    private:
        ~InterfaceAbi() = delete;
    }; //ITaskContext
    //Interface Remap
    template<class TImplementer>
    struct InterfaceRemap<MicroNetwork::Device::ITaskContext, TImplementer> : public InterfaceRemap<MicroNetwork::Common::IDataReceiver, TImplementer>{
        virtual Result LFRAMEWORK_COM_CALL readPackets(){
            Result comCallResult_ = this->implementer()->readPackets();
            return comCallResult_;
        }
        virtual Result LFRAMEWORK_COM_CALL isExitRequested(bool& result){
            Result comCallResult_ = this->implementer()->isExitRequested(result);
            return comCallResult_;
        }
    };
    //Interface Wrapper
    template<>
    class InterfaceWrapper<MicroNetwork::Device::ITaskContext> : public InterfaceWrapper<MicroNetwork::Common::IDataReceiver> {
    public:
        Result readPackets(){
            return reinterpret_cast<InterfaceAbi<MicroNetwork::Device::ITaskContext>*>(_abi)->readPackets();
        } //readPackets
        Result isExitRequested(bool& result){
            return reinterpret_cast<InterfaceAbi<MicroNetwork::Device::ITaskContext>*>(_abi)->isExitRequested(result);
        } //isExitRequested
    };
}
namespace MicroNetwork::Device{
    class ITask;
} //MicroNetwork::Device
namespace LFramework{
    //Interface ABI
    template<>
    struct InterfaceAbi<MicroNetwork::Device::ITask> : public InterfaceAbi<MicroNetwork::Common::IDataReceiver>{
        using Base = InterfaceAbi<MicroNetwork::Common::IDataReceiver>;
        //{f00576e3-8670-4e21-9d21-006b466286fb}
        static constexpr InterfaceID ID() { return { 0xf00576e3, 0x8670, 0x4e21, { 0x9d, 0x21, 0x00, 0x6b, 0x46, 0x62, 0x86, 0xfb } }; }
        virtual Result LFRAMEWORK_COM_CALL run(LFramework::InterfaceAbi<MicroNetwork::Device::ITaskContext>* context) = 0;
    private:
        ~InterfaceAbi() = delete;
    }; //ITask
    //Interface Remap
    template<class TImplementer>
    struct InterfaceRemap<MicroNetwork::Device::ITask, TImplementer> : public InterfaceRemap<MicroNetwork::Common::IDataReceiver, TImplementer>{
        virtual Result LFRAMEWORK_COM_CALL run(LFramework::InterfaceAbi<MicroNetwork::Device::ITaskContext>* context){
            Result comCallResult_ = this->implementer()->run(context);
            return comCallResult_;
        }
    };
    //Interface Wrapper
    template<>
    class InterfaceWrapper<MicroNetwork::Device::ITask> : public InterfaceWrapper<MicroNetwork::Common::IDataReceiver> {
    public:
        Result run(LFramework::ComPtr<MicroNetwork::Device::ITaskContext> context){
            return reinterpret_cast<InterfaceAbi<MicroNetwork::Device::ITask>*>(_abi)->run(context.detach());
        } //run
    };
}

