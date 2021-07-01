#include "pch.h"
#include "Task.h"

Task::Task(int pid, int type, int delay)
{
	this->pid = pid;
	this->type = type;
	this->delay = delay;
}