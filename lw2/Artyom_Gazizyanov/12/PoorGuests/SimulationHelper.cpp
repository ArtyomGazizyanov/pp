#include "stdafx.h"
#include "SimulationHelper.h"
#include "ThreadManager.h"
#include <iostream>
#include "GuestInfo.h"
#include "Reception.h"
#include "Constant.h"
#include <Windows.h>
#include <chrono>
#include <thread>

void SimulationHelper::Start(Hotel* hotel)
{
	GenerateGuests();
	Reception receptionInfo(hotel->GetUnoccupiedNumbers(), &_guestQueue);
	AcceptGuest(&receptionInfo);
	_threadManager.KillAll();
}

void SimulationHelper::GenerateGuests()
{
	unsigned int ammountOfGuests = Constant::MIN_AMMOUNT_OF_GUESTS + rand() % Constant::MAX_AMMOUNT_OF_GUESTS;
	for (unsigned int i = 0; i < ammountOfGuests; ++i)
	{
		unsigned int ammountOfMoney = Constant::MIN_AMMOUNT_OF_MONEY + rand() % Constant::MAX_AMMOUNT_OF_MONEY;
		unsigned int lifetime = Constant::MIN_AMMOUNT_OF_LIFETIME + rand() % Constant::MAX_AMMOUNT_OF_LIFETIME;		 
		Guest guest(ammountOfMoney, lifetime);

		_guestQueue.push_back(guest);
	}
}

DWORD WINAPI SimulationHelper::AcceptGuest(CONST LPVOID data)
{
	Reception* receptionInfo = (Reception*)data;
	while (!receptionInfo->GetGuestQueue()->empty())
	{
		if (receptionInfo->GetGuestQueue()->empty())
		{
			break;
		}

		Guest guest = receptionInfo->GetGuestQueue()->front();
		receptionInfo->GetGuestQueue()->erase(receptionInfo->GetGuestQueue()->begin());
		for (unsigned int i = 0; i < receptionInfo->GetUnoccupiedNumbers()->size(); ++i)
		{
			if (receptionInfo->GetUnoccupiedNumbers()->at(i).first <= guest.GetMoney() && receptionInfo->GetUnoccupiedNumbers()->at(i).second > 0)
			{
				GuestInfo guestInfo(guest.GetLifetime(), &receptionInfo->GetUnoccupiedNumbers()->at(i).second);
				InterlockedDecrement(&receptionInfo->GetUnoccupiedNumbers()->at(i).second);
				_threadManager.AddTask(SimulationHelper::ProcessGuest, &guestInfo);

				break;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}	
	_threadManager.WaitAllTasks();
	
	return 0;
}

DWORD WINAPI SimulationHelper::ProcessGuest(CONST LPVOID data)
{
	GuestInfo* guestInfo = (GuestInfo*) data;
	HANDLE mutex = CreateMutex(NULL, FALSE, (LPCWSTR)"GetGuestMutex");
	std::this_thread::sleep_for(std::chrono::milliseconds(guestInfo->GetLifeTime()));
	InterlockedIncrement(guestInfo->GetUnoccupiedRoomsAmmount());

	return 0;
}
