
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include "Event.h"
#include "Scheduler.h"
#include "FcfsSched.h"
#include "SjfSched.h"
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
	proc.setStatus(1);
	 //completed cpu burst

	int endTime = time + proc.getNextCpuBurst();
	int eventType = 1;
	if (endTime > MaxTime) {
		eventType = 3;
	}
	
	eventQueue->push(Event(endTime, eventType, proc.getProcessId()));
	

	return new Process(proc);
}

//my man the main
int main()
{
	std::priority_queue<Event> eventQueue;
	std::vector<Process*> ioList;
	std::vector<Process*> finished;

	std::cout <<  "Judah Perez, CS 433, Project 3" << std::endl;
	std::cout << "CPU Scheduling" << std::endl;

	std::cout << "Enter number of processing to simulate (1-100). 10 is a good test." << std::endl;
	int testCount;
	std::cin >> testCount;


	LoadEvents(&eventQueue, testCount); //set amount of starting procs

	int time = 0;
	int startIdle = 0;
	int idleTime = 0;
	int procId = 1;
	Scheduler* scheduler;
	
	int schedSelect = 0;
	std::cout << "Select type of scheduler. 0  for First Come First Serve, 1 for Shortest Job First." << std::endl;
	std::cin >> schedSelect;
	//scheduler selection
	if (schedSelect == 0) {
		scheduler = new FcfsSched();
	}
	else {
		scheduler = new SjfSched();
	}
	
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
			proc.setStatus(0);
			scheduler->Add(proc);
			
			if (processInCpu == 0) //idle
			{
				idleTime += time - startIdle;
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
				processInCpu->setStatus(2);
				ioList.push_back(processInCpu);

			}
			else
			{
				//process done
				processInCpu->setFinishTime(time);
				processInCpu->setStatus(3);
				finished.push_back(processInCpu);
			}
			processInCpu = 0;
			//if (processInCpu == 0) //idle

			processInCpu = ScheduleNext(time, &eventQueue, scheduler);
			if (processInCpu == 0) 
			{
				startIdle = time;
			}
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
				proc->setStatus(0);
				scheduler->Add(*proc);

			}

			if (processInCpu == 0) //idle
			{
				//if found idling here, we were not processing anything during io
				idleTime += time - startIdle;
				processInCpu = ScheduleNext(time, &eventQueue, scheduler);
			}

			if (processInCpu == 0) 
			{
				startIdle = time;
			}
		}
			break;
		case 3:
			//throw out timer expiration

			processInCpu->setStatus(3);
			processInCpu = 0;
			if (processInCpu == 0) //idle
			{
				processInCpu = ScheduleNext(time, &eventQueue, scheduler);
			}

			if (processInCpu == 0)
			{
				startIdle = time;
			}
			break;
		}
		
	}

	//find averages

	float throughputSecs = finished.size() / (time / 1000.0f);
	float idlePercent = idleTime / (float)time;
	int utilPercent = (int)((1 - idlePercent) * 100);
	int waitTime = 0;
	int turnaround = 0;

	std::cout << scheduler->Name() << ":" << std::endl;

	for (std::vector<Process*>::iterator it = finished.begin(); it != finished.end(); ++it)
	{
		waitTime += (*it)->WaitingTime();
		turnaround += (*it)->Turnaround();
		(*it)->Print();
	}

	waitTime /= finished.size();
	turnaround /= finished.size();
	std::cout << std::endl;

	std::cout << "CPU Utilization is " << utilPercent << "%" << std::endl;
	std::cout << "Throughput is " << throughputSecs << " jobs / s" << std::endl;
	std::cout << "Average turnaround time: " << (turnaround / 1000.0f) << " s" << std::endl;
	std::cout << "Average wait time: " << (waitTime / 1000.0f) << " s" << std::endl;

	int read;
	std::cin >> read;
}
