#pragma once
class Processor
{
public:
	bool isReady;
	Task *task;
	Processor(int type, bool isReady, int T, int time);
	Processor() {};
};
