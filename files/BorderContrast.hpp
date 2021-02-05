#pragma once
#include "AbstractContrast.hpp"

class BorderContrast final : public AbstractContrast
{
public:

	cv::Mat ContrastImage() override;

	std::map<std::string, std::pair<int, int&>>& factorMap() override;

private:

	int factorContrast = 8;

	int srcCoef = 100;

	int thrCoef = 100;

	std::map<std::string, std::pair<int, int&>> map = { {"cntrCoef" ,{ 20, factorContrast}} , {"srcCoef" ,{ 100, srcCoef}} , {"thrCoef" ,{ 100, thrCoef}} };

};

