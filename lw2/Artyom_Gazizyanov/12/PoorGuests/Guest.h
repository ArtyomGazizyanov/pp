#pragma once
#include "stdafx.h"
#include "RoomType.h"
#include <set>
#include <vector>

class Guest
{
public:
	Guest(unsigned int money, unsigned int lifetime);
	~Guest();
	unsigned int GetMoney();
	unsigned int GetLifetime();
private:
	unsigned int _money;
	unsigned int _lifeTime;
};