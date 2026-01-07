#include "UTILS.h"

std::vector<std::string> Formatting()
{
	/*---[Grab Metadata from available SDRs]---*/

	SoapySDR::KwargsList enumerate = SoapySDR::Device::enumerate();
	if (enumerate.empty()) {
		warn("No devices found! Please check connections...");
		return {};
	}

	okay("Devices found! Creating formatted drivers....");
	vector<string> SDR_MakeDevices;
	printf("---/*Checking Device Compatability...*/---\n");
	for (auto SDR = enumerate.begin(); SDR != enumerate.end(); ++SDR) {

		string SDR_driver;
		string SDR_serial;
		string SDR_MakeDevice;
		try {

			SDR_MakeDevice = "driver=" + SDR_driver + ",serial=" + SDR_serial;
			SDR_MakeDevices.push_back(SDR_MakeDevice);
			info("Total formatted device strings: %zu\n", SDR_MakeDevices.size());

			printf(
				"Driver: %s\n"
				"Serial: %s\n"
				"Label: %s\n"
				"PartID: %s\n"
				"Version: %s\n",
				SDR->at("driver").c_str(), SDR->at("serial").c_str(), SDR->at("label").c_str(),
				SDR->at("part_id").c_str(), SDR->at("version").c_str()
			);

		}
		catch (const std::out_of_range& e) {
			warn("Exception caught: %s", e.what());
			continue;
		}
	}
	return SDR_MakeDevices;
}


