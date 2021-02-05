#include "AbstractThreshold.hpp"

void AbstractThresholdMap::SourceImage(const cv::Mat& src)
{
	this->src = src.clone();
}