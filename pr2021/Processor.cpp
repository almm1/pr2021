#include "pch.h"
#include "Processor.h"


Processor::Processor(bool isReady, int T, int time)
{
	this->isReady = isReady;
	this->T = T;
	this->time = time;
}

