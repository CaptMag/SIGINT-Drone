#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <SoapySDR/Version.hpp>
#include <SoapySDR/Modules.hpp>
#include <SoapySDR/Registry.hpp>
#include <SoapySDR/Device.hpp>
#include <SoapySDR/ConverterRegistry.hpp>
#include <iostream>


#include <string>
#include <vector>

using namespace std;

#define okay(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
#define warn(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("[i] " msg "\n", ##__VA_ARGS__)
#define CHAR(MSG, ...) printf("[>] Press <Enter> to "		MSG "\n", ##__VA_ARGS__)
#define PRINT_ERROR(MSG, ...) fprintf(stderr, "[!] " MSG " Failed! Error: 0x%lx""\n", GetLastError())

std::vector<std::string> Formatting();
SoapySDR::Device* MakeDev();
int enumeration(SoapySDR::Device* device);
std::vector<std::string> ListSensors(SoapySDR::Device* device, const int dir, const size_t chan);
std::vector<std::string> Range_and_Tuning(SoapySDR::Device* device, const int dir, const size_t chan);

#endif