#include "UTILS.h"

int main() {


	_putenv("SOAPY_SDR_PLUGIN_PATH=C:\\Program Files\\PothosSDR\\lib\\SoapySDR\\modules0.8");

	SoapySDR::Device* dev = MakeDev();
	int enum_result = enumeration(dev);
	std::vector<std::string> sensors = ListSensors(dev, SOAPY_SDR_RX, 1);
	std::vector<std::string> Completed_Information = Range_and_Tuning(dev, SOAPY_SDR_RX, 0);

	return EXIT_SUCCESS;
}
