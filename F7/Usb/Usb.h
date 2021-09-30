#pragma once

#include <LFramework/USB/Device/USBDDevice.h>
#include <LFramework/USB/Device/UsbDBulkInterface.h>
#include <LFramework/USB/Device/UsbDDeviceContext.h>

class Usb {
public:
	Usb();

	LFramework::USB::UsbDBulkInterface* usbInterface = nullptr;
	LFramework::USB::UsbDDeviceContext* usbContext = nullptr;
};
