#include "SjfSched.h"



SjfSched::SjfSched()
{
}


SjfSched::~SjfSched()
{
}


void SjfSched::Add(Process proc)
{
	queue.push(proc);
}

bool SjfSched::Empty()
{
	return queue.empty();
}

Process SjfSched::Next()
{
	Process proc = this->Top();
	queue.pop();
	return proc;
}

Process SjfSched::Top()
{
	return queue.top();
}

const char* SjfSched::Name() {
	return "Shortest Job First";
}
