#include "enumeration.h"
#include "UTILS.h"

/*If needed, uncomment these lines for troubleshooting*/

	//info("Default module path: %s", SoapySDR::getRootPath().c_str());


	//auto mods = SoapySDR::listModules();
	//for (auto mod : mods) {
	//	info("Loaded Module: %s", mod.c_str());
	//}

int main() {

	_putenv("SOAPY_SDR_PLUGIN_PATH=C:\\Program Files\\PothosSDR\\lib\\SoapySDR\\modules0.8");

	std::vector<std::string> Formatting();
	SoapySDR::Device* MakeDev();
	int enumeration();
	std::vector<std::string> sensors = ListSensors(MakeDev(), SOAPY_SDR_TX, 1);
	std::vector<std::string> Compledted_Information = Range_and_Tuning(MakeDev(), SOAPY_SDR_TX, 0);
	return EXIT_SUCCESS;
}
