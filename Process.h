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

	int m_finishTime;
	int m_ioTime;
	int m_serviceTime;


public:
	Process(int procId, int startTime);
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

	void setFinishTime(int val);
	void addIoTime(int addTime);
	void addServiceTime(int addTime);

	void Print();



	friend bool operator<(const Process& lhs, const Process& rhs)
	{
		return lhs.m_totalCpuDuration > rhs.m_totalCpuDuration;
	}
};

#endif