#pragma once
#include "stdafx.h"
#include "GuestInfo.h"

GuestInfo::GuestInfo(unsigned int lifetime, unsigned int * unoccupiedRoomsAmmount)
{
	_unoccupiedRoomsAmmount = unoccupiedRoomsAmmount;
	_lifetime = lifetime;
}

unsigned int GuestInfo::GetLifeTime()
{
	return _lifetime;
}

unsigned int* GuestInfo::GetUnoccupiedRoomsAmmount()
{
	return _unoccupiedRoomsAmmount;
}
