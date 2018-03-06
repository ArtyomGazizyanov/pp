#pragma once
#include <Windows.h>
#include <vector>

using namespace std;
class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();
	void KillAll();
	void AddTask(LPTHREAD_START_ROUTINE threadFunction, LPVOID data);
	void WaitAllTasks();

private:
	vector<HANDLE> m_threadHandles;
};
