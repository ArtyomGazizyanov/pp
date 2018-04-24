#pragma once
#include "stdafx.h"

class Guest
{
public:
	Guest(unsigned int money, unsigned int lifetime, unsigned int id);
	~Guest() = default;
	unsigned int GetMoney();
	unsigned int GetLifetime();
	unsigned int GetId();
private:
	unsigned int _money;
	unsigned int _lifeTime;
	unsigned int _id;
};