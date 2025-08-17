#include "UTILS.h"
#include "enumeration.h"


	/*Function designed to check for all 'fine-tunning' and more information about an SDR before data capturing*/


/*Amount of Available Channels*/

std::string GetChannelNum(SoapySDR::Device* device, int dir)
{
	size_t chan_amt = device->getNumChannels(dir);
	return "[i] Total Number of Channels: " + std::to_string(chan_amt);
}


/*Duplexity Checker (either full or half)*/

std::string chk_duplex(SoapySDR::Device* device, int dir, size_t chan)
{
	bool check_duplex = device->getFullDuplex(dir, chan);

	try {
		if (check_duplex == 0)
		{
			return "[*] Specified Channel can only support Half-Duplex ";
		}
		if (check_duplex == 1)
		{
			return  "[*] Specified Channel can support Full Duplex ";
		}
		else
		{
			return "[!] Error retrieving Duplexity.";
		}
	}
	catch (exception& e)
	{
		warn("Could Not specify duplexity %s", e.what());
	}
}


/*List Sample Rate Ranges*/

std::string Sample_Rates(SoapySDR::Device* device, int dir, size_t chan)
{
	try {

		std::vector<double> samp_rate = device->listSampleRates(dir, chan);
		std::string result = "===============[Supported Sample Rates]===============\n";

		for (const auto& rates : samp_rate)
		{
			result += "  -" + std::to_string(rates) + " SPS\n";

		}
		return result;
	}
	catch (std::exception& e)
	{
		warn("Exception Caught: %s", e.what());
		return "[!] Error retrieving Sample Rates.";
	}
}


/*Antenna Name and Information*/
std::string ListAntennas(SoapySDR::Device* device, int dir, size_t chan)
{

	try {

		std::vector<std::string> Antenna_Info = device->listAntennas(dir, chan);
		std::string result = "================[Antenna Information]================\n";

		for (const auto& names : Antenna_Info)
		{
			result += "  -" + names + "\n";
		}
		return result;
	}
	catch (std::exception& e)
	{
		warn("Exception Caught: %s", e.what());
		return "[!] Error retrieving Antenna Info.";
	}
}


/*Displays clock names*/

std::string ClockSource(SoapySDR::Device* device)
{
	try {

		std::vector<std::string> Available_Clocks = device->listClockSources();
		std::string Get_Source = device->getClockSource();
		std::string result = "===============[Supported Clock Sources]================ \n";

		for (const auto& clock : Available_Clocks)
		{
			result += " -" + clock + "\n";
		}
		return result;
	}
	catch (std::exception& e)
	{
		warn("Exception Caught! %s", e.what());
		return "[!] Error retrieving Clock Sourcing Info";
	}
}


/*List Bandwidth Ranges*/

std::string GetBandwidths(SoapySDR::Device* device, int dir, size_t chan)
{

	try {

		std::vector<double> BandWidthRanges = device->listBandwidths(dir, chan);
		std::string result = "===============[List Bandwidth Ranges]===============\n";

		for (const auto& ranges : BandWidthRanges)
		{
			result += "  -" + std::to_string(ranges) + "\n";
		}
		return result;
	}
	catch (std::exception& e)
	{
		warn("Exception Caught: %s", e.what());
		return "[!] Error retrieving BandWidth Ranges.";
	}
}

std::string StreamFormats(SoapySDR::Device* device, const int dir, const size_t chan)
{
	try {

		std::vector<std::string> Formats = device->getStreamFormats(dir, chan);
		std::string result = "===============[Available Stream Formats]===============\n";

		for (const auto& list : Formats)
		{
			result += " -" + list + "\n";
		}
		return result;
	}
	catch (std::exception& e)
	{
		warn("Exception Caught! %s", e.what());
		return "[!] Error Retrieving Streaming Formats";
	}
}

std::vector<std::string> Range_and_Tuning(SoapySDR::Device* device, const int dir, const size_t chan)
{
	
	std::vector<std::string> Completed_Information;
	try {

		if (!device)
		{
			warn("Error! SDR Currently not online, check connections...");
			return { "ERROR" };
		}

		okay("Running Additional SDR Checkers!");

		Completed_Information.push_back(GetChannelNum(device, dir));

		Completed_Information.push_back(chk_duplex(device, dir, chan));

		Completed_Information.push_back(Sample_Rates(device, dir, chan));

		Completed_Information.push_back(ListAntennas(device, dir, chan));

		Completed_Information.push_back(GetBandwidths(device, dir, chan));

		Completed_Information.push_back(ClockSource(device));

		Completed_Information.push_back(StreamFormats(device, dir, chan));

		for (const auto& item : Completed_Information)
		{
			std::cout << item << std::endl;
		}



	}
	catch (std::exception& e) {
		warn("Exception caught %s", e.what());
		return { "ERROR" };
	}
	return Completed_Information;
}
