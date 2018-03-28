#include "Process.h"
#include "random.h"


Process::Process(int procId)
{
	m_processId = procId;

	m_totalCpuDuration = ranInt(1000, 60000);
	m_remainingCpuDuration = m_totalCpuDuration;
	m_avgCpuBurtLength = ranInt(5,100);
	CalcNextCpuBurst();
	m_status = 0;//ready
}


Process::~Process()
{
}


void Process::CalcNextCpuBurst()
{
	m_nextCpuBurstLength = CPUBurstRandom(m_avgCpuBurtLength);
}


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






