#pragma once
#ifndef ENUMERATION_H
#define ENUMERATION_H

#include "UTILS.h"

std::vector<std::string> Formatting();
SoapySDR::Device* MakeDev();
int enumeration();
std::vector<std::string> ListSensors(SoapySDR::Device* device, const int dir, const size_t chan);
std::vector<std::string> Range_and_Tuning(SoapySDR::Device* device, const int dir, const size_t chan);
SoapySDR::Stream* StreamSetup(SoapySDR::Device* device,
	int direction,
	const std::string& format,
	const std::vector<size_t>& channels,
	const SoapySDR::Kwargs& args,
	const int flags = 0,
	const long long timeNs = 0,
	const size_t numElems = 0);
int GUI(SoapySDR::Device* device, SoapySDR::Stream* stream);

#endif#pragma once
