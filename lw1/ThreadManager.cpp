#include "stdafx.h"
#include "ThreadManager.h"


ThreadManager::ThreadManager()
{
}


ThreadManager::~ThreadManager()
{
}

void ThreadManager::KillAll()
{
	for (HANDLE const& threadHandle : m_threadHandles)
	{
		CloseHandle(threadHandle);
	}
}

void ThreadManager::WaitAllTasks()
{
	WaitForMultipleObjects(m_threadHandles.size(), m_threadHandles.data(), TRUE, 1000);
}

void ThreadManager::AddTask(LPTHREAD_START_ROUTINE func, LPVOID data)
{
	m_threadHandles.emplace_back(CreateThread(NULL, NULL, func, data, NULL, NULL));
}