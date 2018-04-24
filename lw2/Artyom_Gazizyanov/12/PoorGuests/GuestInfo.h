#pragma once
class GuestInfo
{
public:
	GuestInfo(unsigned int lifetime, unsigned int* unoccupiedRoomsAmmount, unsigned int userId);
	unsigned int GetLifeTime();
	unsigned int* GetUnoccupiedRoomsAmmount();
	unsigned int GetUserId();
private:
	unsigned int _lifetime;
	unsigned int* _unoccupiedRoomsAmmount;
	unsigned int _userId;
};