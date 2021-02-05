#pragma once

namespace compressImage
{
	static uchar average(std::initializer_list<uchar> _list)
	{
		int aver = 0;
		for (auto it : _list)
		{
			aver = aver + it;
		}
		return aver / 4;
	}
	static cv::Mat compression(const cv::Mat& mat, uchar func(std::initializer_list<uchar>))
	{
		int nRows = mat.rows / 2;
		int nCols = mat.cols / 2;
		if (nRows < 1 && nCols < 1)
		{
			return mat;
		}
		cv::Mat nMap = cv::Mat(nRows, nCols, mat.type());
		//std::cout << nMap.size() << " " << nMap.rows << " " << nMap.cols << " " << nMap.channels() << std::endl;

		for (int y = 0; y < nMap.rows; y++)
		{
			for (int x = 0; x < nMap.cols; x++)
			{
				nMap.at<uchar>(y, x) = func({ mat.at<uchar>(y * 2, x * 2),
				mat.at<uchar>(y * 2 + 1, x * 2 + 1),
				mat.at<uchar>(y * 2 + 1, x * 2),
				mat.at<uchar>(y * 2, x * 2 + 1) });
			}
		}

		return nMap;
	}

	static cv::Mat maxMat(const cv::Mat& mat)
	{
		return compression(mat, std::max);
	}
	static cv::Mat midMat(const cv::Mat& mat)
	{
		return compression(mat, average);
	}
	static cv::Mat minMat(const cv::Mat& mat)
	{
		return compression(mat, std::min);
	}
}
namespace convertColor
{
	static cv::Mat YfromYCrCb(const cv::Mat src)
	{
		cv::Mat ch[3];
		cv::split(src, ch);
		return ch[0].clone();
	}
	static cv::Mat YfromBGR(const cv::Mat src)
	{
		cv::Mat yCrCb;
		cv::cvtColor(src, yCrCb, cv::COLOR_BGR2YCrCb);
		return YfromYCrCb(yCrCb);
	}
}
namespace imageModification
{
	static void sameType(cv::Mat& first, cv::Mat& sec)
	{
		if (first.channels() != sec.channels())
		{
			if (first.channels() != 1)
			{
				cv::cvtColor(first, first, cv::COLOR_BGR2GRAY);
			}

			if (sec.channels() != 1)
			{
				cv::cvtColor(sec, sec, cv::COLOR_BGR2GRAY);
			}
		}
	}
}
