#include <SoapySDR/Version.hpp>
#include <SoapySDR/Modules.hpp>
#include <SoapySDR/Registry.hpp>
#include <SoapySDR/Device.hpp>
#include <SoapySDR/ConverterRegistry.hpp>
#include <iostream>
using namespace std;

#define okay(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
#define warn(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("[i] " msg "\n", ##__VA_ARGS__)

int main() {
	
	try {
		SoapySDR::KwargsList enumerate = SoapySDR::Device::enumerate();

		if (enumerate.empty()) {
			warn("Could not find any devices!");
			return EXIT_FAILURE;
		}

		okay("Devices found! Creating formatted drivers....");
		vector<string> SDR_MakeDevices;
		for (auto SDR = enumerate.begin(); SDR != enumerate.end(); ++SDR) {
			//info("Device Information: %s", SDR->at("driver"));
			printf("---/*Checking Device Compatability...*/---\n");
			string SDR_driver;
			string SDR_serial;
			string SDR_MakeDevice;
			printf("[*] Total formatted device strings: %zu\n", SDR_MakeDevices.size());
			try {
				SDR_serial = SDR->at("serial");
				SDR_driver = SDR->at("driver");
				SDR_MakeDevice = "device=" + SDR_driver + ",serial=" + SDR_serial;
				SDR_MakeDevices.push_back(SDR_MakeDevice);
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
	}
	catch (std::exception& e) {
		warn("Exception caught: %s", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
