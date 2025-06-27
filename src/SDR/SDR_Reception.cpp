#include <SoapySDR/Version.hpp>
#include <SoapySDR/Modules.hpp>
#include <SoapySDR/Registry.hpp>
#include <SoapySDR/Device.hpp>
#include <SoapySDR/ConverterRegistry.hpp>
#include <iostream>
using namespace std;

static std::string DeviceCheck() {
	try {
		SoapySDR::KwargsList result = SoapySDR::Device::enumerate();

		if (result.empty()) {
			std::cout << "No devices found";
			return "";
		} else {
			std::cout << "Devices found!" << std::endl;
			for (auto device = result.begin(); device != result.end(); ++device) {
				std::cout << (*device)["driver"] << std::endl;
				string driver_driver = (*device)["driver"];
				string driver_serial = (*device)["serial"];
				string formatted_driver = "driver=" + driver_driver + ",serial=" + driver_serial;
				return formatted_driver;
			}
			return "";
		}
	}
	catch (std::exception& e) {
		std::cout << "Exception Caught: " << e.what() << std::endl;
		return "";
	}
	std::cout << std::endl;
	return "";
}

static int MakeDevice(const std::string& argStr)
{
	std::cout << "Make Device " << argStr << std::endl;
	try
	{
		auto device = SoapySDR::Device::make(argStr);
		std::cout << "Driver= " << device->getDriverKey() << std::endl;
		std::cout << "Hardware= " << device->getHardwareKey() << std::endl;
		for (const auto& it : device->getHardwareInfo())
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

	std::string args = DeviceCheck();
	if (args.empty()) return EXIT_FAILURE;
	return MakeDevice(args);

	return EXIT_SUCCESS;
}
