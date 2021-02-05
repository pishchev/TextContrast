#pragma once
#include "AbstractContrast.hpp"

class AlphaContrast final : public AbstractContrast
{
public:

	cv::Mat ContrastImage() override;

	std::map<std::string, std::pair<int, int&>>& factorMap() override;

private:

	std::map<std::string, std::pair<int, int&>> map = { {"cntrCoef" ,{ 20, factorContrast}} , {"srcCoef" ,{ 100, srcCoef}},{"thrCoef" ,{ 100, thrCoef}} };

	int factorContrast = 2;

	int srcCoef = 50;

	int thrCoef = 100;
};