#ifndef SJFSCHED_H
#define SJFSCHED_H
#include "Scheduler.h"
#include <queue>

class SjfSched : public Scheduler
{
private:
	std::priority_queue<Process> queue;

public:
	SjfSched();
	~SjfSched();

	void Add(Process proc);
	Process Next();
	Process Top();
	bool Empty();

	const char* Name();
};

#endif

