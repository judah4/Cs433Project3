#include "Event.h"



Event::Event(int time, int eventType, int procId)
{
	m_time = time;
	m_eventType = eventType;
	m_procId = procId;
}


Event::~Event()
{
}


int Event::getTime()
{
	return m_time;
}

int Event::getEventType()
{
	return m_eventType;
}

const char* Event::GetEventName()
{
	switch (m_eventType)
	{
	case 0:
		return "Process Arrival";
	case 1:
		return "CPU Burst Completion";
	case 2:
		return "I/O Completion";
	case 3:
		return "Timer Expiration";
	default:
		return "Unknown";
	}
}


int Event::getProcessId()
{
	return m_procId;
}

