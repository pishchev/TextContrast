#pragma once
#include "AbstractThreshold.hpp"

class compMat
{
private:
	cv::Size srcSize;
	int compLvl = 0;
	cv::Mat mat;
public:
	compMat() = delete;
	compMat(const cv::Mat& mat, int lvl, cv::Size srcSize) :mat(mat), compLvl(lvl), srcSize(srcSize) {};
	cv::Mat getUnCompMat(int interpolation = 1);
	cv::Mat getCompMat();
	int getLvl();
};

class PyramidThresholdMap final : public AbstractThresholdMap
{
public:

	void SourceImage(const cv::Mat& src) override;
	cv::Mat ThresholdMap() override;
	std::map<std::string, std::pair<int, int&>>& factorMap()override;


private:

	std::map<std::string, std::pair<int, int&>> map = { {"lvlPyr" ,{ 5, lvlPyramid } } , {"lvlNoise" ,{ 200, lvlNoise } } ,{"gausCoef" ,{ 40, gausFactor } } };

	int lvlPyramid = 1;
	int lvlNoise = 20;
	int gausFactor = 0;

	void makePyramid(std::vector<compMat>& vec, cv::Mat func(const cv::Mat& mat));
	void minimumPyramid();
	void averagePyramid();
	void maximumPyramid();

	std::vector<compMat> minimumMaps;
	std::vector<compMat> averageMaps;
	std::vector<compMat> maximumMaps;

};