#include "UTILS.h"

/*Grab sensors information from available SDR*/

//This program is designed for Software Defined Radios that have sensoring abilities, only they can be recognized by SoapySDR
//If your SDR does not have this ability (for instance a HackRF) this function is essentially useless.

std::vector<std::string> ListSensors
(
	SoapySDR::Device* device,
	const int dir,
	const size_t chan
)
{

	if (!device) {
		warn("Error! No validated SDR connected, please check connections!");
		return { "ERROR" };
	}

	try {

		okay("Initiating Sensor Checker!");
		std::vector<std::string> sensors = device->listSensors(dir, chan);
		printf("[*] Number of sensors found: %zu\n", sensors.size());

		if (sensors.size() == 0)
		{
			warn("No sensors detected! Operation incomplete!");
			return { "ERROR" };
		}

		for (size_t i = 0; i < sensors.size(); i++)
		{
			try {
				std::string key = sensors[i];
				SoapySDR::ArgInfo SensorInfo = device->getSensorInfo(key);

				printf(
					"Key: %s\n"
					"Value: %s\n"
					"Name: %s\n"
					"Description: %s\n"
					"Units: %s\n",
					SensorInfo.key, SensorInfo.value, SensorInfo.name, SensorInfo.description, SensorInfo.units
				);

			}
			catch (const std::exception& ex)
			{
				warn("Error gathering information: %s", ex.what());
				continue;
			}
		}
	}
	catch (std::exception& e) {
		warn("Exception caught");
		return { "ERROR" };
	}
}
