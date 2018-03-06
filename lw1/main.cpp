#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <memory>
#include <cstdlib>      
#include <ctime>        
#include <cmath>   
#include <string>

#include "CalculatingData.h"
#include "ThreadManager.h"

using namespace std;

double CreateDot()
{
	double x = (double)rand() / (RAND_MAX);
	double y = (double)rand() / (RAND_MAX);

	return sqrt(x*x + y*y);	
}

double GetPi(unsigned int const& allDotsCounter, unsigned int const& inCircleDotsCounter)
{
	return 4.0 * (inCircleDotsCounter / (double)allDotsCounter);	
}

bool IsInCircle(double* dotOriginDistance)
{
	return (*dotOriginDistance) <= 1;
}

void WaitingMutex(HANDLE mutex)
{
	while (WaitForSingleObject(mutex, 0) != WAIT_OBJECT_0)
	{
	}
}

DWORD WINAPI Calculate(CONST LPVOID data)
{
	CalculatingData *calculatingData = (CalculatingData*)data;
	HANDLE mutex = CreateMutex(NULL, FALSE, (LPCWSTR)"GetCreatedNumberOfDotsMutex");
	WaitingMutex(mutex);

	while (calculatingData->GetTotalNumOfDots() != calculatingData->GetDotsAmmountToCreate())
	{
		InterlockedIncrement(calculatingData->GetTotalNumOfDotsPtr());
		ReleaseMutex(mutex);
		double dotOriginDistance = CreateDot();
		if (IsInCircle(&dotOriginDistance))
		{
			InterlockedIncrement(calculatingData->GetInCircleNumOfDotsPtr());
		}
		WaitingMutex(mutex);
	}
	CloseHandle(mutex);

	return 0;
}

DWORD WINAPI PrintStatus(CONST LPVOID data)
{
	CalculatingData *calculatingData = (CalculatingData*)data;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cPos; 

	int UPDATE_DURATION = 1000;
	int PROCENT = 100;

	cPos.Y = 1;
	cPos.X = 0;
	double progress = 0;

	while (progress != PROCENT)
	{
		SetConsoleCursorPosition(hCon, cPos);
		progress = static_cast<double>(calculatingData->GetTotalNumOfDots()) / calculatingData->GetDotsAmmountToCreate() * 100;
		cout << "[" << calculatingData->GetTotalNumOfDots() << " / \"" << calculatingData->GetDotsAmmountToCreate() << "] (" << (int) progress << "% / 100%)" <<  endl;
		Sleep(UPDATE_DURATION);
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	unsigned int numThrows = stoi(argv[1]);
	unsigned int threadCount = stoi(argv[2]);
	unsigned int inCircleDotsCounter = 0;

	shared_ptr<CalculatingData> calculatingData = make_shared<CalculatingData>(CalculatingData({ numThrows, inCircleDotsCounter }));

	ThreadManager threadManager;
	threadManager.AddTask(PrintStatus, calculatingData.get());

	if (threadCount == 1)
	{
		Calculate(calculatingData.get());
	}
	else
	{
		for (unsigned int i = 0; i < threadCount; ++i)
		{
			threadManager.AddTask(Calculate, calculatingData.get());
		}
	}

	threadManager.WaitAllTasks();
	threadManager.KillAll();
	
	cout << "All dots = " << calculatingData->GetTotalNumOfDots() << "  In circle dots = " << calculatingData->GetInCircleNumOfDots() << endl;

	double pieCalc = GetPi((calculatingData->GetTotalNumOfDots()), (calculatingData->GetInCircleNumOfDots()));
	cout << "The value of PI is: " << pieCalc << endl;

	return 0;
}
