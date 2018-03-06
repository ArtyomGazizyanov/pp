#pragma once
#include <cmath>   
class MathHelper
{
public:
	MathHelper();
	static double CreateDot();
	static double GetPi(unsigned int const& allDotsCounter, unsigned int const& inCircleDotsCounter);
	static bool IsInCircle(double* dotOriginDistance);
	~MathHelper();
};