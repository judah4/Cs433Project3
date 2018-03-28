
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include "Event.h"
#include "Scheduler.h"
#include "FcfsSched.h"

//load initial events
void LoadEvents(std::priority_queue<Event>* priorityQueue, int eventsCount)
{
	for(int cnt = 0; cnt <  eventsCount; cnt++)
	{
		priorityQueue->push(Event(0, 0, 0));
	}
}

//send next to cpu and add end event
Process* ScheduleNext(int time, std::priority_queue<Event>* eventQueue, Scheduler* scheduler)
{
	if(scheduler->Empty())
	{
		return 0;
	}

	Process* proc = scheduler->Next();
	 //completed cpu burst
	
	
	eventQueue->push(Event(time+ proc->getNextCpuBurst(), 1, proc->getProcessId()));
	

	return proc;
}

int main()
{
	std::priority_queue<Event> eventQueue;
	std::vector<Process*> ioList;

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
		std::cout << "Current Time:" << time << " Event: " << event.GetEventName() << " Event Time: " << event.getTime() << std::endl;

		switch (event.getEventType())
		{
		case 0:
		{
			int newProcId = procId++;
			Process* proc = new Process(newProcId);
			proc->CalcNextCpuBurst();
			scheduler->Add(proc);
			
			if (processInCpu == 0) //idle
			{
				processInCpu = ScheduleNext(time, &eventQueue, scheduler);
			}
		}
			break;

		case 1:

			processInCpu->setRemainingCpuDuration(processInCpu->getRemainingCpuDuration() - processInCpu->getNextCpuBurst());
			//calced remaining, checking if need to reschedule
			if(processInCpu->getRemainingCpuDuration() > 0)
			{
				//io event
				eventQueue.push(Event(time + processInCpu->getNextCpuBurst(), 2, processInCpu->getProcessId()));
				ioList.push_back(processInCpu);
				
			}
			processInCpu = 0;
			//if (processInCpu == 0) //idle
			
			processInCpu = ScheduleNext(time, &eventQueue, scheduler);
			
			break;
		case 2:

			//todo: find in ioList
			Process * proc = 0;
			for (std::vector<Process*>::iterator it = ioList.begin(); it != ioList.end(); ++it)
			{
				if((*it)->getProcessId() == event.getProcessId())
				{
					proc = *it;
					ioList.erase(it);
					break;
				}
			}
			//remove from ioList

			if(proc == 0)
			{
				throw "We could not find!";
			}
			

			proc->CalcNextCpuBurst();
			

			//calced remaining, checking if need to reschedule
			if (proc->getRemainingCpuDuration() > 0)
			{
				scheduler->Add(proc);

			}

			if (processInCpu == 0) //idle
			{
				processInCpu = ScheduleNext(time, &eventQueue, scheduler);
			}

			break;
		}
		
	}



	int read;
	std::cin >> read;
}
