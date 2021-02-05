#pragma once

#include "AbstractContrast.hpp"

class SaturationContrast final : public AbstractContrast
{
public:

	void SourceImage(const cv::Mat& src) override;

	void ThresholdMap(const cv::Mat& thresholdMap) override;

	cv::Mat ContrastImage() override;

	std::map<std::string, std::pair<int, int&>>& factorMap() override;


private:

	void makeHVS();
	void makeYCrCb();


	int factorContrast = 0;
	int critCoef = 200;

	std::map<std::string, std::pair<int, int&>> map = { {"critCoef" ,{ 500, critCoef}},{ "cntrCoef" , {1000,factorContrast} } };

	cv::Mat yCrCb;
	cv::Mat hsv;
};
