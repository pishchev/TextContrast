#include "AbstractContrast.hpp"

void AbstractContrast::SourceImage(const cv::Mat& src)
{
	this->src = src.clone();
}
void AbstractContrast::ThresholdMap(const cv::Mat& thresholdMap)
{
	this->thresholdMap = thresholdMap.clone();
}