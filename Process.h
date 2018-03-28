#ifndef PROCESS_H
#define PROCESS_H

class Process
{
private:
	int m_processId;
	int m_startTime;//in ms
	int m_totalCpuDuration;
	int m_remainingCpuDuration;
	int m_avgCpuBurtLength;
	int m_nextCpuBurstLength;
	int m_ioBurstTime;
	int m_status; //0 ready, 1 running, 2 waiting, 3 terminated


public:
	Process(int procId);
	~Process();

	void CalcNextCpuBurst();
	void CalcNextIoBurst();

	int getStatus();
	void setStatus(int val);
	int Priority();

	int getNextCpuBurst();
	int getNextIoBurst();
	int getRemainingCpuDuration();
	void setRemainingCpuDuration(int val);
	int getTotalCpuDuration();
	int getProcessId();



	friend bool operator<(const Process& lhs, const Process& rhs)
	{
		return lhs.m_totalCpuDuration > rhs.m_totalCpuDuration;
	}
};

#endif