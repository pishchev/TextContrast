#include "Contrast.hpp"
#include "ImageUtils.hpp"
#include <iostream>

void ContrastMaker::Init(int, void* user)
{
	auto self = reinterpret_cast<ContrastMaker*>(user);
	cv::resize(self->src, self->resizedSrc, cv::Size(), static_cast<double>(self->imageSize) / 100 + 0.1, static_cast<double>(self->imageSize) / 100 + 0.1);
	self->thresholdMap->SourceImage(self->resizedSrc);
	self->contrast->SourceImage(self->resizedSrc);
	self->factorsThresholdMap = self->thresholdMap->factorMap();
	self->factorsContrastMap = self->contrast->factorMap();

	Make(1, self);
}
void ContrastMaker::Make(int, void* user)
{
	auto self = reinterpret_cast<ContrastMaker*>(user);
	cv::Mat th = self->thresholdMap->ThresholdMap();
	self->contrast->ThresholdMap(th);
	self->res = self->contrast->ContrastImage();

	cv::Mat doubleImage;

	imageModification::sameType(self->resizedSrc, self->res);

	cv::hconcat(self->resizedSrc, self->res, doubleImage);

	cv::imshow("Res", doubleImage);
}
void ContrastMaker::UI()
{
	Init(1, this);
	cv::destroyWindow("Regulate");
	cv::namedWindow("Regulate", cv::WINDOW_NORMAL);
	cv::createTrackbar("ImageSize", "Regulate", &imageSize, 100, Init, this);
	for (auto it = factorsThresholdMap.begin(); it != factorsThresholdMap.end(); ++it)
	{
		cv::createTrackbar(it->first, "Regulate", &(it->second.second), it->second.first, Make, this);
	}
	for (auto it = factorsContrastMap.begin(); it != factorsContrastMap.end(); ++it)
	{
		cv::createTrackbar(it->first, "Regulate", &(it->second.second), it->second.first, Make, this);
	}
}
cv::Mat ContrastMaker::resultImage()
{
	int imageSizeBack = imageSize;
	imageSize = 90;
	Init(1, this);
	cv::Mat fullSizeResult = res.clone();
	imageSize = imageSizeBack;
	Init(1, this);
	return fullSizeResult;
}
void ContrastMaker::newThresholdMap(std::unique_ptr<AbstractThresholdMap>&& thrMap)
{
	thresholdMap = std::move(thrMap);
	Init(1, this);
}
void ContrastMaker::newContrastMap(std::unique_ptr<AbstractContrast>&& cntrMap)
{
	contrast = std::move(cntrMap);
	Init(1, this);
}
void ContrastMaker::newSourceMap(const cv::Mat src)
{
	this->src = src.clone();
}

Contrast::Contrast() : cmaker(std::make_unique<GaussianThresholdMap>(), std::make_unique<BorderContrast>()) {}
void Contrast::mainLoop()
{
	if (!sourceImage())
	{
		return;
	}

	cv::namedWindow("Type", cv::WINDOW_NORMAL);

	bool repeat = true;

	while (repeat)
	{
		std::cout << "Menu:" << std::endl << "SAVE IMAGE - 1" << std::endl << "NEW IMAGE - 2" << std::endl << "EXIT - 0" << std::endl;

		contrastImage();

		cv::createTrackbar("cntrType", "Type", &ctrType, MapTypes::countCtrTypes - 1, changeTypes, this);
		cv::createTrackbar("thrType", "Type", &thrType, MapTypes::countThrtypes - 1, changeTypes, this);

		int key = cv::waitKey();

		if (key == '1')
		{
			saveImage();
		}
		else if (key == '2')
		{
			if (!sourceImage())
			{
				return;
			}
		}
		else if (key == '0')
		{
			repeat = false;
		}

	}
}
void Contrast::printResult() const
{
	cv::imshow("Result", result);
}
bool Contrast::sourceImage()
{
	bool repeat = true;
	bool error = false;

	while (repeat)
	{
		if (error)
		{
			std::cout << "CAN'T OPEN IMAGE, TRY AGAIN. ENTER 0 TO EXIT" << std::endl;
		}

		std::cout << "NAME OF THE IMAGE: ";
		std::string fileName;
		std::getline(std::cin, fileName);

		if (fileName == "0")
		{
			return false;
		}

		src = cv::imread(fileName);
		if (src.data != nullptr)
		{
			repeat = false;
		}
		else
		{
			error = true;
		}
	}
	cmaker.newSourceMap(src);
	return true;
}
void Contrast::contrastImage()
{
	cmaker.UI();
}
void Contrast::saveImage()
{
	result = cmaker.resultImage();
	std::string fileName;

	std::cout << "NAME OF THE NEW IMAGE: ";

	std::getline(std::cin, fileName);
	bool check = cv::imwrite(fileName, result);
	if (check == false)
	{
		std::cout << "SAVING THE IMAGE - FAILED" << std::endl;
	}
	else
	{
		std::cout << "SAVING THE IMAGE - SUCCESS" << std::endl;
	}
}
void Contrast::changeTypes(int, void* user)
{
	auto self = reinterpret_cast<Contrast*>(user);

	std::unique_ptr<AbstractContrast> ctr;
	std::unique_ptr<AbstractThresholdMap> thr;

	switch (self->ctrType)
	{
	case MapTypes::Border:
		self->cmaker.newContrastMap(std::make_unique<BorderContrast>());
		break;
	case MapTypes::Alpha:
		self->cmaker.newContrastMap(std::make_unique<AlphaContrast>());
		break;
	case MapTypes::Saturation:
		self->cmaker.newContrastMap(std::make_unique<SaturationContrast>());
		break;
	}

	switch (self->thrType)
	{
	case MapTypes::Gaussian:
		self->cmaker.newThresholdMap(std::make_unique<GaussianThresholdMap>());
		break;
	case MapTypes::Pyramid:
		self->cmaker.newThresholdMap(std::make_unique<PyramidThresholdMap>());
		break;
	}

	(*self).contrastImage();
}