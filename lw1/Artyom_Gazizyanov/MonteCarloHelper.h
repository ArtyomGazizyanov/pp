#pragma once
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <memory>
#include <cstdlib>      
#include <ctime>
#include <string>
#include "CalculatingData.h"

class MonteCarloHelper
{
public:
	MonteCarloHelper();
	static void WaitingMutex(HANDLE mutex);
	static void CalculateDots(CalculatingData* calculatingData, HANDLE mutex = NULL);
	static DWORD WINAPI Calculate(CONST LPVOID data);
	static DWORD WINAPI PrintStatus(CONST LPVOID data);
	~MonteCarloHelper();
};