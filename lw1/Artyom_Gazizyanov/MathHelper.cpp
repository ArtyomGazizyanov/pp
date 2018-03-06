#include "stdafx.h"
#include "MathHelper.h"

MathHelper::MathHelper()
{
}

MathHelper::~MathHelper()
{
}

double MathHelper::CreateDot()
{
	double x = (double)rand() / (RAND_MAX);
	double y = (double)rand() / (RAND_MAX);

	return sqrt(x*x + y*y);
}

double MathHelper::GetPi(unsigned int const& allDotsCounter, unsigned int const& inCircleDotsCounter)
{
	return 4.0 * (inCircleDotsCounter / (double)allDotsCounter);
}

bool MathHelper::IsInCircle(double* dotOriginDistance)
{
	return (*dotOriginDistance) <= 1;
}
