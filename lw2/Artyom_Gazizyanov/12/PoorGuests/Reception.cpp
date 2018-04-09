#include "stdafx.h"
#include "Reception.h"

Reception::Reception(std::vector<std::pair<unsigned int, unsigned int>>* unoccupiedNumbers, std::vector<Guest>* guestQueue)
{
	_unoccupiedNumbers = unoccupiedNumbers;
	_guestQueue = guestQueue;
}

Reception::~Reception()
{
}

std::vector<std::pair<unsigned int, unsigned int>>* Reception::GetUnoccupiedNumbers()
{
	return _unoccupiedNumbers;
}

std::vector<Guest>* Reception::GetGuestQueue()
{
	return _guestQueue;
}
