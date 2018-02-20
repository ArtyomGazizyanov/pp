#include "stdafx.h"
#include "CalculatingData.h"

CalculatingData::CalculatingData(unsigned int dotsAmountToCreate, unsigned int inCircleDotsCounter):
	m_numOfDotsPtr(std::make_shared<unsigned int>(0)),
	m_numOfDotsInCirclePtr(std::make_shared<unsigned int>(inCircleDotsCounter)),
	m_dotsAmountToCreate(std::make_shared<unsigned int>(dotsAmountToCreate))
{
}

CalculatingData::~CalculatingData()
{
}

unsigned int CalculatingData::GetInCircleNumOfDots()
{
	return *m_numOfDotsInCirclePtr.get();
}

unsigned int CalculatingData::GetDotsAmmountToCreate()
{
	return *m_dotsAmountToCreate.get();
}

unsigned int CalculatingData::GetTotalNumOfDots()
{
	return *m_numOfDotsPtr.get();
}

unsigned int* CalculatingData::GetInCircleNumOfDotsPtr()
{
	return m_numOfDotsInCirclePtr.get();
}

unsigned int* CalculatingData::GetTotalNumOfDotsPtr()
{
	return m_numOfDotsPtr.get();
}

void CalculatingData::ChangeTotalNumOfDots(unsigned int changer)
{
	*m_numOfDotsPtr = *m_numOfDotsPtr + changer;
}

void CalculatingData::ChangeInCircleNumOfDots(unsigned int changer)
{
	(*m_numOfDotsInCirclePtr) = (*m_numOfDotsInCirclePtr) + changer;
}

