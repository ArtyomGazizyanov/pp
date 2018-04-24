#include "stdafx.h"
#include "ThreadManager.h"
#include "GuestInfo.h"
#include "Reception.h"
#include "Constant.h"
#include "Hotel.h"
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "SimulationHelper.h"

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
		Guest guest(ammountOfMoney, lifetime, i);

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
		bool hasStay = false;
		receptionInfo->GetGuestQueue()->erase(receptionInfo->GetGuestQueue()->begin());
		for (unsigned int i = 0; i < receptionInfo->GetUnoccupiedNumbers()->size(); ++i)
		{
			if (receptionInfo->GetUnoccupiedNumbers()->at(i).second <= guest.GetMoney() && receptionInfo->GetUnoccupiedNumbers()->at(i).first > 0)
			{
				GuestInfo guestInfo(guest.GetLifetime(), &receptionInfo->GetUnoccupiedNumbers()->at(i).second, guest.GetId());
				InterlockedDecrement(&receptionInfo->GetUnoccupiedNumbers()->at(i).second);
				_threadManager.AddTask(SimulationHelper::ProcessGuest, &guestInfo);
				hasStay = true;
				break;
			}
		}
		if (!hasStay)
		{
			std::cout << "Guest #" << guest.GetId() << " hasn`t enough money" << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}	
	_threadManager.WaitAllTasks();
	
	return 0;
}

DWORD WINAPI SimulationHelper::ProcessGuest(CONST LPVOID data)
{
	GuestInfo* guestInfo = (GuestInfo*) data;
	std::cout << "Guest #" << guestInfo->GetUserId() << " has arrived at room" << std::endl;
	HANDLE mutex = CreateMutex(NULL, FALSE, (LPCWSTR)"GetGuestMutex");
	std::this_thread::sleep_for(std::chrono::milliseconds(guestInfo->GetLifeTime()));
	InterlockedIncrement(guestInfo->GetUnoccupiedRoomsAmmount());
	std::cout << "Guest #" << guestInfo->GetUserId() << " left room" << std::endl;

	return 0;
}
