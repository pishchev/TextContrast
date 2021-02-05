#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <string>
#include <map>
#include <memory>

#include "ContrastPool.hpp"

namespace MapTypes
{
	static int countThrtypes = 2;
	enum thresholdTypes
	{
		Gaussian,
		Pyramid
	};

	static int countCtrTypes = 3;
	enum contrastTypes
	{
		Border,
		Alpha,
		Saturation
	};

}

class ContrastMaker
{
public:

	ContrastMaker(std::unique_ptr<AbstractThresholdMap>&& thresholdMap, std::unique_ptr<AbstractContrast>&& contrast) : thresholdMap(std::move(thresholdMap)), contrast(std::move(contrast)) {};
	static void Init(int, void* user);
	static void Make(int, void* user);

	void newSourceMap(const cv::Mat src);
	void newThresholdMap(std::unique_ptr<AbstractThresholdMap>&& thresholdMap);
	void newContrastMap(std::unique_ptr<AbstractContrast>&& thresholdMap);

	cv::Mat resultImage();

	void UI();
private:
	cv::Mat src;
	cv::Mat resizedSrc;
	cv::Mat res;
	int imageSize = 30;

	std::unique_ptr<AbstractThresholdMap> thresholdMap;
	std::unique_ptr<AbstractContrast> contrast;

	std::map<std::string, std::pair<int, int&>> factorsThresholdMap;
	std::map<std::string, std::pair<int, int&>> factorsContrastMap;

};

class Contrast
{
public:
	Contrast();
	void mainLoop();

private:

	cv::Mat src;
	cv::Mat result;
	int ctrType = MapTypes::Border;
	int thrType = MapTypes::Gaussian;
	ContrastMaker cmaker;



	void printResult() const;
	bool sourceImage();
	void contrastImage();
	void saveImage();
	static void changeTypes(int, void* user);
};

