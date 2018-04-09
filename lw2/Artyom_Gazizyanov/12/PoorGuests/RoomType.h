#pragma once
#pragma once
class RoomType
{
public:
	RoomType(unsigned int roomAmmount, unsigned int price);
	~RoomType();
	unsigned int GetRoomAmmount();
	unsigned int GetPrice();
private:
	unsigned int _roomAmmount;
	unsigned int _price;
};