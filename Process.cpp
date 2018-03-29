#include "Process.h"
#include "random.h"

#include <iostream>       // std::cout


Process::Process(int procId, int startTime)
{
	m_processId = procId;
	m_startTime = startTime;

	m_totalCpuDuration = ranInt(1000, 60000); //1 second to 1 minute
	m_remainingCpuDuration = m_totalCpuDuration;
	m_avgCpuBurtLength = ranInt(5,100);
	CalcNextCpuBurst();
	m_status = 0;//ready

	m_finishTime = -1;
	m_serviceTime = 0;
	m_ioTime = 0;

}


Process::~Process()
{
}

//next cpu burst
void Process::CalcNextCpuBurst()
{
	m_nextCpuBurstLength = CPUBurstRandom(m_avgCpuBurtLength);
}

//next io burst
void Process::CalcNextIoBurst()
{
	m_ioBurstTime = ranInt(30, 100);
}

int Process::Priority()
{
	return m_totalCpuDuration;
}

int Process::getStatus()
{
	return m_status;
}

void Process::setStatus(int val)
{
	m_status = val;
}

int Process::getNextCpuBurst()
{
	return m_nextCpuBurstLength;
}

int Process::getNextIoBurst()
{
	return m_nextCpuBurstLength;
}

int Process::getRemainingCpuDuration()
{
	return m_remainingCpuDuration;
}

void Process::setRemainingCpuDuration(int val)
{
	m_remainingCpuDuration = val;
}

int Process::getTotalCpuDuration()
{
	return m_totalCpuDuration;
}


int Process::getProcessId()
{
	return m_processId;
}

void Process::setFinishTime(int val) {
	m_finishTime = val;
}
void Process::addIoTime(int addTime) {
	m_ioTime += addTime;
}
void Process::addServiceTime(int addTime) {
	m_serviceTime += addTime;
}

int Process::Turnaround()
{
	return m_finishTime - m_startTime;
}
int Process::WaitingTime()
{
	return m_finishTime - m_startTime - m_serviceTime - m_ioTime;
}

void Process::Print() 
{
	std::cout << "Process " << m_processId << ":" << std::endl;
	std::cout << "arrival time: " << (m_startTime / 1000.0f) << " s" << std::endl;
	std::cout << "finish time: " << (m_finishTime / 1000.0f) << " s" << std::endl;
	std::cout << "service time: " << (m_serviceTime / 1000.0f) << " s" << std::endl;
	std::cout << "I/O time: " << (m_ioTime / 1000.0f) << " s" << std::endl;
	std::cout << "turnaround time: " << ((Turnaround()) / 1000.0f) << " s" << std::endl;
	std::cout << "waiting time: " << ((WaitingTime()) / 1000.0f) << " s" << std::endl;
}

