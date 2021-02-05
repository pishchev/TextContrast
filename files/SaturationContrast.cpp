#include "SaturationContrast.hpp"

void SaturationContrast::makeHVS()
{
	cv::cvtColor(src, hsv, cv::COLOR_BGR2HLS);
}
void SaturationContrast::makeYCrCb()
{
	cv::cvtColor(src, yCrCb, cv::COLOR_BGR2YCrCb);
}
cv::Mat SaturationContrast::ContrastImage()
{
	cv::Mat result = yCrCb.clone();

	cv::Mat resBGR;

	for (int i = 0; i < yCrCb.rows; i++)
	{
		for (int p = 0; p < yCrCb.cols; p++)
		{
			double c = hsv.at<cv::Vec3b>(i, p)[1];
			double coef = 0;
			if (c < 1)
			{
				coef = static_cast<double>(critCoef) / 100;
			}
			else
			{
				coef = (static_cast<double>(factorContrast)) / c;
				if (coef > static_cast<double>(critCoef) / 100) coef = static_cast<double>(critCoef) / 100;
			}
			double l = -yCrCb.at<cv::Vec3b>(i, p)[0] + static_cast<double>(thresholdMap.at<uchar>(i, p));
			double r = coef * l;
			result.at<cv::Vec3b>(i, p)[0] = r;
		}
	}

	cv::cvtColor(result, resBGR, cv::COLOR_YCrCb2BGR);

	return resBGR;
}
void SaturationContrast::SourceImage(const cv::Mat& src)
{
	this->src = src.clone();

	cv::cvtColor(src, yCrCb, cv::COLOR_BGR2YCrCb);
	cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

}
void SaturationContrast::ThresholdMap(const cv::Mat& thresholdMap)
{
	this->thresholdMap = thresholdMap.clone();

	if (thresholdMap.channels() != 1)
	{
		cv::cvtColor(this->thresholdMap, this->thresholdMap, cv::COLOR_BGR2GRAY);
	}
}
std::map<std::string, std::pair<int, int&>>& SaturationContrast::factorMap()
{
	return map;
}