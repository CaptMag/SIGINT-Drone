#pragma once
#ifndef ENUMERATION_H
#define ENUMERATION_H

#include "UTILS.h"

std::vector<std::string> Formatting();
SoapySDR::Device* MakeDev();
int enumeration();
std::vector<std::string> ListSensors(SoapySDR::Device* device, const int dir, const size_t chan);
std::vector<std::string> Range_and_Tuning(SoapySDR::Device* device, const int dir, const size_t chan);

#endif#pragma once
