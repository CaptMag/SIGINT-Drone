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

	std::vector<std::string> fmt = Formatting();
	SoapySDR::Device* dev = MakeDev();
	int enum_result = enumeration();
	std::vector<std::string> sensors = ListSensors(dev, SOAPY_SDR_RX, 1);
	std::vector<std::string> Completed_Information = Range_and_Tuning(dev, SOAPY_SDR_RX, 0);
	SoapySDR::Stream* stream = StreamSetup(dev, SOAPY_SDR_RX, "CF32", { 0 }, {}, 0, 0, 0);
	auto gui_result = GUI(dev, stream);

	return EXIT_SUCCESS;
}
