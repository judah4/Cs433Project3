
#ifndef EVENT_H
#define EVENT_H

class Event
{
private:
	int  m_time; //in milliseconds
	int m_eventType; //event value
	int m_procId;

public:
	Event(int time, int eventType, int procId);
	~Event();
	int getTime();
	int getEventType();
	const char* GetEventName();
	int getProcessId();

	friend bool operator<(const Event& lhs, const Event& rhs)
	{
		return lhs.m_time > rhs.m_time;
	}
};



#endif
