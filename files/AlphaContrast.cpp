#include "AlphaContrast.hpp"
#include "ImageUtils.hpp"

cv::Mat AlphaContrast::ContrastImage()
{
	imageModification::sameType(src, thresholdMap);

	cv::Mat contrastMat;

	cv::addWeighted(src, -static_cast<double>(srcCoef)/100, thresholdMap, static_cast<double>(thrCoef)/100, 0, contrastMat);

	contrastMat.convertTo(contrastMat, -1, 1, 0);

	contrastMat = src - contrastMat;

	contrastMat.convertTo(contrastMat, -1, static_cast<double>(factorContrast), 0);

	return contrastMat;
}
std::map<std::string, std::pair<int, int&>>& AlphaContrast::factorMap()
{
	return map;
}