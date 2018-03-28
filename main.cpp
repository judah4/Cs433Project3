
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include "Event.h"
#include "Scheduler.h"
#include "FcfsSched.h"
#include "random.h"

int MaxTime = 300000;//ms

//load initial events
void LoadEvents(std::priority_queue<Event>* priorityQueue, int eventsCount)
{
	for(int cnt = 0; cnt <  eventsCount; cnt++)
	{
		priorityQueue->push(Event(ranInt(0, MaxTime), 0, 0));
	}
}

//send next to cpu and add end event
Process* ScheduleNext(int time, std::priority_queue<Event>* eventQueue, Scheduler* scheduler)
{
	if(scheduler->Empty())
	{
		return 0;
	}

	Process proc = scheduler->Next();
	 //completed cpu burst
	
	eventQueue->push(Event(time+ proc.getNextCpuBurst(), 1, proc.getProcessId()));
	

	return new Process(proc);
}

int main()
{
	std::priority_queue<Event> eventQueue;
	std::vector<Process*> ioList;
	std::vector<Process*> finished;

	std::cout <<  "Judah Perez, CS 433, Project 3" << std::endl;
	std::cout << "CPU Scheduling" << std::endl;

	LoadEvents(&eventQueue, 10); //set amount of starting procs

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
			std::cout << "Event queue Out of order! Current:" << time << "ms Event Time:" << event.getTime() << "ms" << std::endl;
		}
		else
		{
			time = event.getTime();
		}


		eventQueue.pop();
		std::cout << "Current Time:" << time << "ms Event: " << event.GetEventName() << " Event Time: " << event.getTime() << "ms" << std::endl;

		switch (event.getEventType())
		{
		case 0:
		{
			int newProcId = procId++;
			Process proc = Process(newProcId, event.getTime());
			proc.CalcNextCpuBurst();
			scheduler->Add(proc);
			
			if (processInCpu == 0) //idle
			{
				processInCpu = ScheduleNext(time, &eventQueue, scheduler);
			}
		}
			break;

		case 1:
		{
			int serviceTime = processInCpu->getNextCpuBurst();
			processInCpu->setRemainingCpuDuration(processInCpu->getRemainingCpuDuration() - serviceTime);
			processInCpu->addServiceTime(serviceTime);
			//calced remaining, checking if need to reschedule
			if (processInCpu->getRemainingCpuDuration() > 0)
			{
				//io event
				processInCpu->CalcNextIoBurst();
				eventQueue.push(Event(time + processInCpu->getNextIoBurst(), 2, processInCpu->getProcessId()));

				ioList.push_back(processInCpu);

			}
			else
			{
				//process done
				processInCpu->setFinishTime(time);
				finished.push_back(processInCpu);
			}
			processInCpu = 0;
			//if (processInCpu == 0) //idle

			processInCpu = ScheduleNext(time, &eventQueue, scheduler);
		}
			break;
		case 2:
		{
			//todo: find in ioList
			Process* proc = 0;
			for (std::vector<Process*>::iterator it = ioList.begin(); it != ioList.end(); ++it)
			{
				if ((*it)->getProcessId() == event.getProcessId())
				{
					proc = new Process(*(*it)); //ewe
					ioList.erase(it);
					break;
				}
			}
			//remove from ioList

			if (proc == 0)
			{
				throw "We could not find!";
			}

			proc->addIoTime(proc->getNextIoBurst());

			proc->CalcNextCpuBurst();


			//calced remaining, checking if need to reschedule
			if (proc->getRemainingCpuDuration() > 0)
			{
				scheduler->Add(*proc);

			}

			if (processInCpu == 0) //idle
			{
				processInCpu = ScheduleNext(time, &eventQueue, scheduler);
			}
		}
			break;
		}
		
	}

	for (std::vector<Process*>::iterator it = finished.begin(); it != finished.end(); ++it)
	{
		(*it)->Print();
	}



	int read;
	std::cin >> read;
}
