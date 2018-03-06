#include "stdafx.h"

#include "MonteCarloHelper.h"
#include "CalculatingData.h"
#include "ThreadManager.h"
#include "MathHelper.h"

MonteCarloHelper::MonteCarloHelper()
{
}

MonteCarloHelper::~MonteCarloHelper()
{
}

void MonteCarloHelper::WaitingMutex(HANDLE mutex)
{
	while (WaitForSingleObject(mutex, 0) != WAIT_OBJECT_0)
	{
	}
}

DWORD WINAPI MonteCarloHelper::Calculate(CONST LPVOID data)
{
	CalculatingData *calculatingData = (CalculatingData*)data;
	HANDLE mutex = CreateMutex(NULL, FALSE, (LPCWSTR)"GetCreatedNumberOfDotsMutex");
	WaitingMutex(mutex);

	MonteCarloHelper::CalculateDots(calculatingData, mutex);
	CloseHandle(mutex);

	return 0;
}

void MonteCarloHelper::CalculateDots(CalculatingData* calculatingData, HANDLE mutex)
{
	while (calculatingData->GetTotalNumOfDots() != calculatingData->GetDotsAmmountToCreate())
	{
		InterlockedIncrement(calculatingData->GetTotalNumOfDotsPtr());
		if(mutex != NULL)
		{
			ReleaseMutex(mutex);
		}
		double dotOriginDistance = MathHelper::CreateDot();
		if (MathHelper::IsInCircle(&dotOriginDistance))
		{
			InterlockedIncrement(calculatingData->GetInCircleNumOfDotsPtr());
		}
		if (mutex != NULL)
		{
			MonteCarloHelper::WaitingMutex(mutex);
		}
	}
}

DWORD WINAPI MonteCarloHelper::PrintStatus(CONST LPVOID data)
{
	CalculatingData *calculatingData = (CalculatingData*)data;

	int UPDATE_DURATION = 1000;
	int PROCENT = 100;
	double progress = 0;

	while (progress != PROCENT)
	{
		progress = static_cast<double>(calculatingData->GetTotalNumOfDots()) / calculatingData->GetDotsAmmountToCreate() * 100;
		cout << "[" << calculatingData->GetTotalNumOfDots() << " / \"" << calculatingData->GetDotsAmmountToCreate() << "] (" << (int)progress << "% / 100%) \r";
		Sleep(UPDATE_DURATION);
	}
	cout << endl;

	return 0;
}
