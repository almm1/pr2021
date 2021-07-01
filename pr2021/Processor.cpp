#include "pch.h"
#include "Processor.h"

Processor::Processor(int type ,bool isReady, int T, int time) {
	this->isReady = isReady;
	this->task.pid = T;
	this->task.delay = time;
	this->task.type = type;
}