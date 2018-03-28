
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include "Event.h"
#include "Scheduler.h"
#include "FcfsSched.h"

void LoadEvents(std::priority_queue<Event>* priorityQueue, int eventsCount)
{
	for(int cnt = 0; cnt <  eventsCount; cnt++)
	{
		priorityQueue->push(Event(0, 0));
	}
}

Process* ScheduleNext(int time, std::priority_queue<Event>* eventQueue, Scheduler* scheduler, int newEventType)
{
	if(scheduler->Empty())
	{
		return 0;
	}

	Process* proc = scheduler->Next();
	if (newEventType == 1) {
		proc->CalcNextCpuBurst();
		eventQueue->push(Event(time+ proc->getNextCpuBurst(), newEventType));
	}

	return proc;
}

int main()
{
	std::priority_queue<Event> eventQueue;

	std::cout <<  "Judah Perez, CS 433, Project 3" << std::endl;
	std::cout << "CPU Scheduling" << std::endl;

	LoadEvents(&eventQueue, 20); //set amount of starting procs

	int time = 0;
	int procId = 1;
	Scheduler* scheduler;
	
	//scheduler selection
	scheduler = new FcfsSched();
	Process* processInCpu = 0;

	while (!eventQueue.empty()) {

		Event event = eventQueue.top();

		if(time > event.getTime())
		{
			std::cout << "Event queue Out of order! Current:" << time << " Event Time:" << event.getTime() << std::endl;
		}
		else
		{
			time = event.getTime();
		}


		eventQueue.pop();
		std::cout << "Current Time:" << time << "Event: " << event.GetEventName() << " Event Time: " << event.getTime() << std::endl;

		switch (event.getEventType())
		{
		case 0:
			scheduler->Add(new Process(procId++));
			if(processInCpu == 0) //idle
			{
				processInCpu = ScheduleNext(time, &eventQueue, scheduler, 1);
			}
			break;
		}



	}

	int read;
	std::cin >> read;
}
