#include "enumeration.h"

	/*Grab sensors information from available SDR*/

//This program is designed for Software Defined Radios that have sensoring abilities, only they can be recognized by SoapySDR
//If your SDR does not have this ability (for instance a HackRF) this function is essentially useless.

std::vector<std::string> ListSensors(SoapySDR::Device *device, const int dir, const size_t chan)
{
	try {

		if (!device) {
			warn("Error! No validated SDR connected, please check connections!");
			return { "ERROR" };
		}
			
			okay("Initiating Sensor Checker!");
			std::vector<std::string> sensors = device->listSensors(dir, chan);
			printf("[*] Number of sensors found: %zu\n", sensors.size());
			std::vector<std::string> Results;

			for (size_t i = 0; i < sensors.size(); i++)
			{
				try {
						std::string key = sensors[i];
						SoapySDR::ArgInfo SensorInfo = device->getSensorInfo(key);
						string SensorReading = device->readSensor(key);


						string Formatted_String = "Key: " + SensorInfo.key + "\nValue: " + SensorInfo.value + "\nName: " + SensorInfo.name + "\nDescription: " + SensorInfo.description +
							"\nUnits: " + SensorInfo.units + "\nReading Information: " + SensorReading;

						Results.push_back(Formatted_String);

						okay("Complete Sensor Values: %s", Formatted_String.c_str());
				}
				catch (const std::exception& ex)
				{
					warn("Error gathering information: %s", ex.what());
					continue;
				}
			}
			return Results;
	}
	catch (std::exception& e) {
		warn("Exception caught");
		return { "ERROR" };
	}
}
