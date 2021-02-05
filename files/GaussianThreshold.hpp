#pragma once
#include "AbstractThreshold.hpp"

class GaussianThresholdMap final : public AbstractThresholdMap
{
public:
	cv::Mat ThresholdMap() override;
	std::map<std::string, std::pair<int, int&>>& factorMap() override;

private:

	std::map<std::string, std::pair<int, int&>> map = { {"gausCoef" ,{ 120, gausFactor } } };
	int gausFactor = 8;

};