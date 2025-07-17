#include <SoapySDR/Device.hpp>
#include <sstream>
#include <limits>
#include "Capture.h"
#include "UTILS.h"

template <typename Type>
std::string toString(const std::vector<Type> &options)
{
	std::stringstream ss;
	if (options.empty()) return "";
	for (size_t i = 0; i < options.size(); i++)
	{
		if (not ss.str().empty()) ss << ", ";
		ss << options[i];
	}
	return ss.str();
}

std::string toString(const SoapySDR::Range& range)
{
	std::stringstream ss;
	ss << "[" << range.minimum() << ", " << range.maximum();
	if (range.step() != 0.0) ss << ", " << range.step();
	ss << "]";
	return ss.str();
}

std::string toString(const SoapySDR::RangeList& range, const double scale)
{
	const size_t MAXRLEN = 10;
	std::stringstream ss;
	for (size_t i = 0; i < range.size(); i++)
	{
		if (range.size() >= MAXRLEN and i >= MAXRLEN / 2 and i < (range.size() - MAXRLEN / 2))
		{
			if (i == MAXRLEN) ss << ", ...";
			continue;
		}
		if (not ss.str().empty()) ss << ", ";
		if (range[i].minimum() == range[i].maximum()) ss << (range[i].minimum()/scale);
		else ss << "[" << (range[i].minimum()/scale) << ", " << (range[i].maximum()/scale) << "]";
	}
	return ss.str();
}

std::string toString(const std::vector<double>& nums, const double scale)
{
	std::stringstream ss;

	if (nums.size() > 3)
	{
		ss << "[" << (nums.front() / scale) << ", " << (nums.back() / scale) << "]";
		return ss.str();
	}

	for (size_t i = 0; i < nums.size(); i++)
	{
		if (not ss.str().empty()) ss << ", ";
		ss << (nums[i] / scale);
	}
	return "[" + ss.str() + "]";
}

std::string toString(const SoapySDR::ArgInfo& argInfo, const std::string indent = "   ")
{
	std::stringstream ss;

	std::string name = argInfo.name;
	if (argInfo.name.empty()) name = argInfo.key;
	ss << indent << " * " << name;

	std::string desc = argInfo.description;
	const std::string replace("\n" + indent + "  ");
	for (size_t pos = 0; (pos = desc.find("\n", pos)) != std::string::npos; pos += replace.size())
	{
		desc.replace(pos, 1, replace);
	}
	if (not desc.empty()) ss << " - " << desc << std::endl << indent << "  ";

	ss << " [key=" << argInfo.key;
	if (not argInfo.units.empty()) ss << ", units=" << argInfo.units;
	if (not argInfo.value.empty()) ss << ", default=" << argInfo.value;


	switch (argInfo.type)
	{
	case SoapySDR::ArgInfo::BOOL: ss << ", type=bool"; break;
	case SoapySDR::ArgInfo::INT: ss << ", type=int"; break;
	case SoapySDR::ArgInfo::FLOAT: ss << ", type=float"; break;
	case SoapySDR::ArgInfo::STRING: ss << ", type=string"; break;
	}

	if (argInfo.range.minimum() < argInfo.range.maximum()) ss << ", range=" << toString(argInfo.range);
	if (not argInfo.options.empty()) ss << ", options=(" << toString(argInfo.options) << ")";

	ss << "]";

	return ss.str();
}

std::string toString(const SoapySDR::ArgInfoList& argInfols)
{
	std::stringstream ss;

	for (size_t i = 0; i < argInfols.size(); i++)
	{
		ss << toString(argInfols[i]) << std::endl;
	}

	return ss.str();
}

std::string sensorReadings(SoapySDR::Device *device)
{
	std::stringstream ss;
	std::vector<std::string> sensors = device->listSensors();

	for (size_t i = 0; i < sensors.size(); i++)
	{
		std::string key = sensors[i];
		SoapySDR::ArgInfo info = device->getSensorInfo(key);
		std::string reading = device->readSensor(key);

		ss << "    " << sensors[i];
		if (not info.name.empty()) ss << " (" << info.name << ")";
		ss << ":";
		if (info.range.maximum() > std::numeric_limits<double>::min()) ss << toString(info.range);
		ss << toString(info.options);
		ss << " " << reading;
		if (not info.units.empty()) ss << " " << info.units;
		ss << std::endl;
		if (not info.description.empty()) ss << "    " << info.description << std::endl;
	}

	return ss.str();
}

std::string ChannelSensorReading(SoapySDR::Device *device, const int dir, const size_t chan)
{
	std::stringstream ss;

	std::vector<std::string> sensors = device->listSensors(dir, chan);

	for (size_t i = 0; i < sensors.size(); i++)
	{
		std::string key = sensors[i];
		SoapySDR::ArgInfo info = device->getSensorInfo(key);
		std::string reading = device->readSensor(key);

		if (info.name.empty()) ss << " (" << info.name << ")";
		ss << ":";
		if (info.range.maximum() > std::numeric_limits<double>::min()) ss << toString(info.range);
		ss << toString(info.options);
		ss << " " << reading;
		if (not info.units.empty()) ss << " " << info.units;
		ss << std::endl;
		if (not info.description.empty()) ss << "    " << info.description << std::endl;

		okay("Everything is in order and ToString is working!");
	}

	return ss.str();
}

//std::string ChanSenRead(SoapySDR::Device *device, const int dir, const size_t chan)
//{
//
//}