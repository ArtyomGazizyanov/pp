#include "stdafx.h"
#include "Guest.h"

Guest::Guest(unsigned int money, unsigned int lifetime, unsigned int id)
{
	if (money < 0 || lifetime == 0)
	{
		throw std::invalid_argument("Ammount of money or lifetime can`t be equal to 0");
	}
	_money = money;
	_lifeTime = lifetime;
	_id = id;
}

unsigned int Guest::GetMoney()
{
	return _money;
}

unsigned int Guest::GetLifetime()
{
	return _lifeTime;
}

unsigned int Guest::GetId()
{
	return _id;
}
