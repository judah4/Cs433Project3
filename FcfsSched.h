#ifndef FCFSSCHED_H
#define FCFSSCHED_H
#include "Scheduler.h"
#include <queue>

class FcfsSched : public Scheduler
{
private:
	std::queue<Process> queue;

public:
	FcfsSched();
	~FcfsSched();

	void Add(Process proc);
	Process Next();
	Process* Top();
	bool Empty();
};

#endif

