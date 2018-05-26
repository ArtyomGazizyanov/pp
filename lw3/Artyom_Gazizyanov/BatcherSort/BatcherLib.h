#pragma once
#include <vector>
#include <omp.h>

using namespace std;

template <typename T>
class BatcherLib
{
public:
	static void Compexch(T& a, T& b);
	static void Sort(std::vector<T>& vector);
};

template <typename T>
void BatcherLib<T>::Sort(std::vector<T>& vectorToSort)
{
	int logOfSize, evenSize, q, leftBorder, rightBorder;
	logOfSize = (int)(ceil(log2(vectorToSort.size())));
	evenSize = (int)(pow(2, logOfSize - 1));
	while (evenSize > 0)
	{
		leftBorder = 0;
		rightBorder = evenSize;

		#pragma omp parallel for
		for (q = (int)(pow(2, logOfSize - 1)); q >= evenSize; q /=2)
		{
			#pragma omp parallel for
			for (int i = 0; i < (int)(vectorToSort.size() - rightBorder); i++)
			{
				if ((i & evenSize) == leftBorder)
				{
					Compexch(vectorToSort[i], vectorToSort[i + rightBorder]);
				}
			}

			rightBorder = q - evenSize;
			leftBorder = evenSize;
		}

		evenSize /= 2;
	}
}

template <typename T>
void BatcherLib<T>::Compexch(T& a, T&b)
{
	if (b < a)
	{
		std::swap(a, b);
	}
}
