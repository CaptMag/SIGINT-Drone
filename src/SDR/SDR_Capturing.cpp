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

std::string capturing(const int dir, const size_t chan) {
	SoapySDR::KwargsList result = SoapySDR::Device::enumerate();
	for (auto device = result.begin(); device != result.end(); ++device) {
		string SDR_Driver = device->at("driver");
		string SDR_Serial = device->at("serial");
		string Formatted_Device = "device=" + SDR_Driver + ",serial=" + SDR_Serial;

		SoapySDR::Device* Device = SoapySDR::Device::make(Formatted_Device);

		/*******************************************************************
		 * Channel sensor readings
		 ******************************************************************/

		std::vector<std::string> sensors = Device->listSensors(dir, chan);

		for (size_t i = 0; i < sensors.size(); i++) {
			try {
				std::string key = sensors[i];
				SoapySDR::ArgInfo info = Device->getSensorInfo(dir, chan, key);
				std::string reading = Device->readSensor(dir, chan, key);

				//info("Reading sensor information: %s", sensors[i]);
				std::cout << "     * " << sensors[i];
				std::cout << "Sensor Reading: " << Device << std::endl;
				//if (not info.name.empty()) info(" (%s}", info.name);
				//if (info.range.maximum() > std::numeric_limits<double>::min()) okay("InfoRange= %s", );
			}
			catch (std::exception& e) {
				warn("Exception caught: %s", e.what());
				return "";
		}
	}
}

