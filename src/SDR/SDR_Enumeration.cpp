#include "UTILS.h"
#include "enumeration.h"

int enumeration() {
	try {

		/*---[Create device for SDR probbing]---*/

		std::vector<std::string> SDR_MakeDevices = Formatting();

		for (const auto& SDR_MakeDevice : SDR_MakeDevices) {
			try {
				info("Make Device: %s", SDR_MakeDevice.c_str());
				auto device = SoapySDR::Device::make(SDR_MakeDevice);
				if (!device) {
					warn("Could not create device for %s", SDR_MakeDevice.c_str());
					continue;
				}
				info("Driver= %s", device->getDriverKey().c_str());
				info("Hardware= %s", device->getHardwareKey().c_str());
				for (const auto& it : device->getHardwareInfo()) {
					std::cout << " " << it.first << "=" << it.second << std::endl;
				}
				SoapySDR::Device::unmake(device);
			}
			catch (const std::exception& ex) {
				warn("Error making device: %s", ex.what());
				continue;
			}

		}
	}
	catch (std::exception& e) {
		warn("Exception caught: %s", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
