#pragma once
#include "Hotel.h"
#include "Guest.h"
#include "ThreadManager.h"
#include <vector>
#include <Windows.h>

class SimulationHelper
{
public:
	void Start(Hotel *hotel);
	void GenerateGuests();
private:
	DWORD WINAPI AcceptGuest(CONST LPVOID data);
	static DWORD WINAPI ProcessGuest(CONST LPVOID data);
	static bool _isWorking;
	std::vector<Guest> _guestQueue;
	Hotel* _hotel;
	ThreadManager _threadManager;
};
