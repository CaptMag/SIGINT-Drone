#include "UTILS.h"

SoapySDR::Device* MakeDev()
{
	try {

		std::vector<std::string> MakeDev = Formatting();

		for (const auto& SDR_MakeDevice : MakeDev)
		{
			okay("SDR Device Creation: %s", SDR_MakeDevice.c_str());

			SoapySDR::Device* device = SoapySDR::Device::make(SDR_MakeDevice);
			if (!device)
			{
				warn("Could not create a valid SDR Device! %s", SDR_MakeDevice.c_str());
				continue;
			}
			return device;
		}
	}
	catch (std::exception& e)
	{
		warn("Exception caught: %s", e.what());
		return nullptr;
	}
}


int enumeration(SoapySDR::Device* device) {
	try {

		/*---[Create device for SDR probing]---*/

		info("Driver= %s", device->getDriverKey().c_str());
		info("Hardware= %s", device->getHardwareKey().c_str());

		for (const auto& it : device->getHardwareInfo()) {
			info(" %s=%s", it.first.c_str(), it.second.c_str());
		}
	}
	catch (std::exception& e) {
		warn("Exception caught: %s", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}