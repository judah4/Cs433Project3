#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Process.h"

class Scheduler {
public:
	// pure virtual function providing interface framework.
	virtual void Add(Process* proc) = 0;
	virtual Process* Next() = 0;
	virtual Process* Top() = 0;
	virtual bool Empty() = 0;

};
#endif

