#include "enumeration.h"

std::vector<std::string> Formatting()
{
	/*---[Grab Metadata from available SDRs]---*/

		SoapySDR::KwargsList enumerate = SoapySDR::Device::enumerate();
		if (enumerate.empty()) {
			warn("No devices found! Please check connections...");
		}
		else {

			okay("Devices found! Creating formatted drivers....");
			vector<string> SDR_MakeDevices;
			printf("---/*Checking Device Compatability...*/---\n");
			for (auto SDR = enumerate.begin(); SDR != enumerate.end(); ++SDR) {

				string SDR_driver;
				string SDR_serial;
				string SDR_MakeDevice;
				try {

					SDR_serial = SDR->at("serial");
					SDR_driver = SDR->at("driver");
					SDR_MakeDevice = "driver=" + SDR_driver + ",serial=" + SDR_serial;
					SDR_MakeDevices.push_back(SDR_MakeDevice);
					printf("[*] Total formatted device strings: %zu\n", SDR_MakeDevices.size());
					string SDR_label = SDR->at("label");
					string SDR_part_id = SDR->at("part_id");
					string SDR_version = SDR->at("version");

					string SDR_complete = SDR_driver + " " + SDR_serial + " " + SDR_label + " " + SDR_part_id + " " + SDR_version;
					okay("Complete information for all devices: %s", SDR_complete.c_str());

				}
				catch (const std::out_of_range& e) {
					warn("Exception caught: %s", e.what());
					continue;
				}
			}
			return SDR_MakeDevices;
		}
}


