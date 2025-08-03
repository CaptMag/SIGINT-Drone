#include "UTILS.h"
#include "enumeration.h"

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
