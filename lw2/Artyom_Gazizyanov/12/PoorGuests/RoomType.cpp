#include "stdafx.h"
#include "RoomType.h"
#include <stdexcept>  

RoomType::RoomType(unsigned int roomAmmount, unsigned int price)
{
	if (roomAmmount == 0 || price == 0)
	{
		throw std::invalid_argument("Ammount of rooms or price can`t be equal to 0");
	}

	_roomAmmount = roomAmmount;
	_price = price;
}

unsigned int RoomType::GetRoomAmmount()
{
	return _roomAmmount;
}

unsigned int RoomType::GetPrice()
{
	return _price;
}
