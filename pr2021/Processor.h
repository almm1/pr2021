#pragma once
class Processor
{
public:
	bool isReady;
	int T;
	int time;
	Processor(bool isReady, int T, int time);
	Processor() {};
};
