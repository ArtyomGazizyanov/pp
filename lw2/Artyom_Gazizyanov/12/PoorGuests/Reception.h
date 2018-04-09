#pragma once
#include <vector>
#include "Guest.h"

class Reception
{
public:
	Reception(std::vector<std::pair<unsigned int, unsigned int>>* _unoccupiedNumbers, std::vector<Guest>* _guestQueue);
	~Reception();
	std::vector<std::pair<unsigned int, unsigned int>>* GetUnoccupiedNumbers();
	std::vector<Guest>* GetGuestQueue();

private:
	std::vector<std::pair<unsigned int, unsigned int>>* _unoccupiedNumbers;
	std::vector<Guest>* _guestQueue;
};