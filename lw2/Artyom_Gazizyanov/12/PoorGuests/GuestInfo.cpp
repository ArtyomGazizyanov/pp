#pragma once
#include "stdafx.h"
#include "GuestInfo.h"

GuestInfo::GuestInfo(unsigned int lifetime, unsigned int * unoccupiedRoomsAmmount, unsigned int userId)
{
	_unoccupiedRoomsAmmount = unoccupiedRoomsAmmount;
	_lifetime = lifetime;
	_userId = userId;
}

unsigned int GuestInfo::GetLifeTime()
{
	return _lifetime;
}

unsigned int* GuestInfo::GetUnoccupiedRoomsAmmount()
{
	return _unoccupiedRoomsAmmount;
}

unsigned int GuestInfo::GetUserId()
{
	return _userId;
}