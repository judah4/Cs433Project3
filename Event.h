
#ifndef EVENT_H
#define EVENT_H

class Event
{
private:
	int  m_time; //in milliseconds
	int m_eventType; //event value

public:
	Event();
	~Event();
	int getTime();
	int getEventType();

	friend bool operator<(const Event& lhs, const Event& rhs)
	{
		return lhs.m_time < rhs.m_time;
	}
};



#endif
