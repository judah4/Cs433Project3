#include "FcfsSched.h"



FcfsSched::FcfsSched()
{
}


FcfsSched::~FcfsSched()
{
}

void FcfsSched::Add(Process proc)
{
	queue.push(proc);
}

bool FcfsSched::Empty()
{
	return queue.empty();
}

Process FcfsSched::Next()
{
	Process proc = this->Top();
	queue.pop();
	return proc;
}

Process FcfsSched::Top()
{
	return queue.front();
}


const char* FcfsSched::Name() {
	return "First Come First Served";
}



