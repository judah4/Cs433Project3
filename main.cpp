
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include "Event.h"

void LoadEvents(std::priority_queue<Event>* priorityQueue, int eventsCount)
{
	for(int cnt = 0; cnt <  eventsCount; cnt++)
	{
		priorityQueue->push(Event(0, 0));
	}
}

int main()
{
	std::priority_queue<Event> priorityQueue;

	std::cout <<  "Judah Perez, CS 433, Project 3" << std::endl;
	std::cout << "CPU Scheduling" << std::endl;

	LoadEvents(&priorityQueue, 20);

	Event event = priorityQueue.top();

	std::cout << "Top Event: " << event.GetEventName() << std::endl;

	int read;
	std::cin >> read;
}
