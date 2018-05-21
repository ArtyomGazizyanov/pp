#pragma once
#include <vector>
#include <omp.h>

using namespace std;

template <typename T>
class BatcherLib
{
public:
	static void OddEvenMergeSort(std::vector<T>& a, unsigned int l, unsigned int r);
	static void Unshuffle(std::vector<T>& a, unsigned int l, unsigned int r);
	static void Shuffle(std::vector<T>& a, unsigned int l, unsigned int r);
	static void Sort(std::vector<T>& vector);
	static void Compexch(T& a, T& b);
};

template <typename T>
void BatcherLib<T>::OddEvenMergeSort(std::vector<T>& a, unsigned int l, unsigned int r)
{
	if (r == l + 1)
	{
		BatcherLib<T>::Compexch(a[l], a[r]);
	}
	if (r < l + 2)
	{
		return;
	}
	BatcherLib<T>::Unshuffle(a, l, r); 
	auto half = (unsigned int)(l + r) / 2;
	BatcherLib<T>::OddEvenMergeSort(a, l, half);
	BatcherLib<T>::OddEvenMergeSort(a, half + 1, r);
	BatcherLib<T>::Shuffle(a, l, r);
	for (auto i = l; i < r; i += 2)
	{
		BatcherLib<T>::Compexch(a[i], a[i + 1]);
	}
	auto halfSize = (r - l + 1) / 2; 
	for (int i = l + 1; i + halfSize < r; i++)
	{
		BatcherLib<T>::Compexch(a[i], a[i + halfSize]);
	}
}

template <typename T>
void BatcherLib<T>::Unshuffle(std::vector<T>& a, unsigned int l, unsigned int r)
{
	auto half = (unsigned int)(l + r) / 2;
	std::vector<T> tmp(a.size());
	unsigned int i, j;
	for (i = l, j = 0; i <= r; i += 2, j++)
	{
		tmp[l + j] = a[i];
		tmp[half + j + 1] = a[i + 1];
	}
	for (auto i = l; i <= r; i++)
	{
		a[i] = tmp[i];
	}
}

template <typename T>
void BatcherLib<T>::Shuffle(std::vector<T>& a, unsigned int l, unsigned int r)
{
	auto half = (unsigned int)(l + r) / 2;
	std::vector<T> tmp(a.size());
	unsigned int i, j;
	for (i = l, j = 0; i <= r; i += 2, j++)
	{
		tmp[i] = a[l + j];
		tmp[i + 1] = a[half + j + 1];
	}
	for (auto i = l; i <= r; i++)
	{
		a[i] = tmp[i];
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

template <typename T>
void BatcherLib<T>::Sort(std::vector<T>& vectorToSort)
{
	int logOfSize, evenSize, q, leftBorder, rightBorder;
	logOfSize = (int)(ceil(log2(vectorToSort.size())));
	evenSize = (int)(pow(2, logOfSize - 1));
	while (evenSize > 0)
	{
		q = (int)(pow(2, logOfSize - 1));
		leftBorder = 0;
		rightBorder = evenSize;
		while (q >= evenSize)
		{
			#pragma omp parallel for
			for (int i = 0; i < (int)(vectorToSort.size() - rightBorder); i++)
			{
				if ((i & evenSize) == leftBorder)
				{
					Compexch(vectorToSort[i],vectorToSort[i + rightBorder]);
				}
			}
			
			rightBorder = q - evenSize;
			q /= 2;
			leftBorder = evenSize;
		}
		evenSize /= 2;
	}
}