#include "GaussianThreshold.hpp"

cv::Mat GaussianThresholdMap::ThresholdMap()
{
	cv::Mat thresholdMap;
	cv::GaussianBlur(src, thresholdMap, cv::Size(gausFactor * 2 + 1, gausFactor * 2 + 1), 0, 0);
	return thresholdMap;
}
std::map<std::string, std::pair<int, int&>>& GaussianThresholdMap::factorMap()
{
	return map;
}