#include "Event.h"



Event::Event(int time, int eventType)
{
	m_time = time;
	m_eventType = eventType;
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

