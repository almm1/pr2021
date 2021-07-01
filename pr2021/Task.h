#pragma once
class Task
{
public:
	Task();
	Task(int pid, int type, int delay);
	int pid;
	int type;
	int delay;
};
