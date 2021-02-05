#include "PyramidThreshold.hpp"
#include "ImageUtils.hpp"

cv::Mat compMat::getCompMat()
{
	return mat;
}
cv::Mat compMat::getUnCompMat(int interpolation)
{
	cv::Mat uncmat;
	cv::resize(mat, uncmat, srcSize, 0, 0, interpolation);

	return uncmat;
}
int compMat::getLvl()
{
	return compLvl;
}

void PyramidThresholdMap::SourceImage(const cv::Mat& src)
{
	this->src = src.clone();

	if (src.channels() != 1)
	{
		this->src = convertColor::YfromBGR(src);
	}

	minimumPyramid();
	averagePyramid();
	maximumPyramid();
}
cv::Mat PyramidThresholdMap::ThresholdMap()
{
	cv::Mat thresholdMap;
	thresholdMap = averageMaps.back().getCompMat().clone();

	int lvl = averageMaps.back().getLvl() - 1;

	for (int i = lvl; i >= lvlPyramid; i--)
	{
		cv::Mat min = minimumMaps[i].getCompMat();
		cv::Mat max = maximumMaps[i].getCompMat();
		cv::Mat aver = averageMaps[i].getCompMat();

		cv::GaussianBlur(thresholdMap, thresholdMap, cv::Size(gausFactor * 2 + 1, gausFactor * 2 + 1), 0, 0);
		cv::resize(thresholdMap, thresholdMap, min.size(), 0, 0, 1);

		for (int y = 0; y < thresholdMap.rows; y++)
		{
			for (int x = 0; x < thresholdMap.cols; x++)
			{
				if ((max.at<uchar>(y, x) - min.at<uchar>(y, x)) >= lvlNoise)
				{
					thresholdMap.at<uchar>(y, x) = aver.at<uchar>(y, x) + 7;
				}
			}
		}

	}
	cv::resize(thresholdMap, thresholdMap, src.size(), 0, 0, 1);
	return thresholdMap;
}
std::map<std::string, std::pair<int, int&>>& PyramidThresholdMap::factorMap()
{
	return map;
}

void PyramidThresholdMap::makePyramid(std::vector<compMat>& vec, cv::Mat func(const cv::Mat& mat))
{
	cv::Mat nMat = src.clone();
	int compLvl = 1;
	while (nMat.rows > 1 && nMat.cols > 1)
	{
		cv::Size srcSize = nMat.size();

		nMat = func(nMat);
		vec.push_back(compMat(nMat, compLvl, srcSize));
		compLvl++;
	}
}
void PyramidThresholdMap::minimumPyramid()
{
	makePyramid(minimumMaps, compressImage::minMat);
}
void PyramidThresholdMap::averagePyramid()
{
	makePyramid(averageMaps, compressImage::midMat);
}
void PyramidThresholdMap::maximumPyramid()
{
	makePyramid(maximumMaps, compressImage::maxMat);
}