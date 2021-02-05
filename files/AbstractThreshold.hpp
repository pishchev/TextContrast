#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <string>
#include <map>

class AbstractThresholdMap
{
public:
	virtual void SourceImage(const cv::Mat& src);
	virtual cv::Mat ThresholdMap() = 0;
	virtual std::map<std::string, std::pair<int, int&>>& factorMap() = 0;

protected:
	cv::Mat src;
};