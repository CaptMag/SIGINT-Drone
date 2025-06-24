#include <SoapySDR/Version.hpp>
#include <SoapySDR/Modules.hpp>
#include <SoapySDR/Registry.hpp>
#include <SoapySDR/Device.hpp>
#include <SoapySDR/ConverterRegistry.hpp>
#include <iostream>

const char* s = "[+]";
const char* f = "[-]";
const char* c = "[*]";

static int DeviceCheck() {
	try {
		SoapySDR::KwargsList result = SoapySDR::Device::enumerate();

		if (result.empty());
		std::cout << "No devices found";
		return EXIT_FAILURE;
	}
	catch (int e) {
		std::cout << "Exception Caught: " << e;
	}
}

static int MakeDevice(const std::string& argStr)
{
	std::cout << "Make Device " << argStr << std::endl;
	try
	{
		auto device = SoapySDR::Device::make(argStr);
		std::cout << "Driver= " << device->getDriverKey() << std::endl;
		std::cout << "Hardware= " << device->getHardwareKey() << std::endl;
		for (const auto &it : device->getHardwareInfo())
		{
			std::cout << "  " << it.first << "=" << it.second << std::endl;
		}
		SoapySDR::Device::unmake(device);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error making device: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << std::endl;
	return EXIT_SUCCESS;
}


int main() {

	DeviceCheck();
	MakeDevice();

	return EXIT_SUCCESS;
}
