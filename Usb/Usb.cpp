#include "Usb.h"

#include <LFramework/Debug.h>
#include <LFramework/Threading/Thread.h>


Usb::Usb(){
	usbInterface = new LFramework::USB::UsbDBulkInterface();
	usbContext = new LFramework::USB::UsbDDeviceContext(usbInterface);

	usbContext->configurationStringDescriptor = "LFramework";
	usbContext->interfaceStringDescriptor = "LFramework";
	usbContext->productStringDescriptor = "LFramework test device";
	usbContext->manufacturerStringDescriptor = "L";
	usbContext->serialStringDescriptor = "123456";
	LFramework::USB::UsbDevice::start(usbContext);

	lfDebug() << "USB started: waiting for interface open...";
	auto usbInterface = usbContext->getInterface(0);
	while(!usbInterface->isOpen()){
		LFramework::Threading::ThisThread::sleepForMs(1);
	}
	lfDebug() << "USB interface is open!";
}
