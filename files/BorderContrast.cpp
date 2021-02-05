#include "BorderContrast.hpp"
#include "ImageUtils.hpp"

std::map<std::string, std::pair<int, int&>>& BorderContrast::factorMap()
{
	return map;
}
cv::Mat BorderContrast::ContrastImage()
{
	imageModification::sameType(src, thresholdMap);

	cv::Mat contrastMat;

	cv::addWeighted(src, -static_cast<double>(srcCoef)/100 , thresholdMap, static_cast<double>(thrCoef)/100, 0, contrastMat);
	contrastMat.convertTo(contrastMat, -1, static_cast<double>(factorContrast), 0);

	cv::bitwise_not(contrastMat, contrastMat);

	return contrastMat;
}