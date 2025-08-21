#include "enumeration.h"

int enumeration(SoapySDR::Device *device) {
	try {

		/*---[Create device for SDR probbing]---*/

		info("Driver= %s", device->getDriverKey().c_str());
		info("Hardware= %s", device->getHardwareKey().c_str());
		for (const auto& it : device->getHardwareInfo()) {
			std::cout << " " << it.first << "=" << it.second << std::endl;
		}
	}
	catch (std::exception& e) {
		warn("Exception caught: %s", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

