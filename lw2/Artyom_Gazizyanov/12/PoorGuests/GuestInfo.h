#pragma once
class GuestInfo
{
public:
	GuestInfo(unsigned int lifetime, unsigned int* unoccupiedRoomsAmmount);
	unsigned int GetLifeTime();
	unsigned int* GetUnoccupiedRoomsAmmount();
private:
	unsigned int _lifetime;
	unsigned int* _unoccupiedRoomsAmmount;
};