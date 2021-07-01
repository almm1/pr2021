#include "pch.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include "Task.h"
#include "windows.h"
#include "Processor.h"
#include <stack> 

Processor P1; //Процессор P1
Processor P2; // P2
Processor P3; // P3

int work_time;//время работы системы
int latency;//задержка генерации задач

Task task; //задача
std::stack <Task> steck;//стек
std::stack <int> done;//массив с выполнеными задачами

int shet(int x) { //функция счета цифр в числе
	int n = 1;
	while ((x /= 10) > 0) n++;
	return n;
}

void print_stack() { //отображение стека
	std::cout << "+-";
	for (std::stack<Task> temp = steck; !temp.empty(); temp.pop())
		std::cout << ' ' << temp.top().pid;
	std::cout << " -+\n";
}

void print_done() { //отображение выполненных задач
	if (done.empty() == false) {
		std::cout << "+-";
		for (std::stack<int> temp = done; !temp.empty(); temp.pop())
			std::cout << ' ' << temp.top();
		std::cout << " -+\n";
	}
}

void print_task(int t, int type) { //отображение задачи выбранного процессора(3 варианта, зависит от количетсва цифр в числе)
	if (shet(t)==1)
		std::cout << "+-- Процессор P"<< type <<": " << t << " ----+\n";
	else if (shet(t)==2)
		std::cout << "+-- Процессор P"<< type <<": " << t << " ---+\n";
	else if (shet(t)==3)
		std::cout << "+-- Процессор P"<< type <<": " << t << " --+\n";
}

void print_work_time() {
	if (shet(work_time) == 1)
		std::cout << "+---------- " << work_time << " ----------+\n";
	else if (shet(work_time) == 2)
		std::cout << "+---------- " << work_time << " ---------+\n";
	else if (shet(work_time) == 3)
		std::cout << "+--------- " << work_time << " ---------+\n";
}
	

void print() { //функция отображения симуляции
	print_work_time();
	std::cout << "+-----------------------+\n";
	print_task(P1.T, 1);
	print_task(P2.T, 2);
	print_task(P3.T, 3);
	std::cout << "+-----------------------+\n";
	std::cout << "+-------- Стек: --------+\n";
	print_stack();
	std::cout << "+-----------------------+\n";
	std::cout << "+------ Выполнено: -----+\n";
	print_done();
	std::cout << "+-----------------------+\n";
}

Task pop()//эмулятор очереди, который является генератором задач
{
	int pid = 1 + rand() % 1000;
	int type = 1 + rand() % 3;
	int delay = 1 + rand() % 10;

	Task *task = new Task(pid, type, delay);
	return *task;
}

void init() {
	work_time = 0;
	latency = 0;
	P1 = Processor(true, 0, 0);
	P2 = Processor(true, 0, 0);
	P3 = Processor(true, 0, 0);
}

void generator() {
	if (latency > 0) {
		latency--;
		task.type = -1;
	}
	else {
		latency = 1 + rand() % 3;
		task = pop();
	}
}

void update_screen() {
	system("CLS");
	print();
	Sleep(1000);
}

void check_proc() {
	if (task.type == 1) {
		if (P1.isReady) {
			P1.isReady = false;
			P1.T = task.pid;
			P1.time = task.delay;
		}
		else {
			steck.push(task);
		}
	}
	else if (task.type == 2) {
		if (P2.isReady) {
			P2.isReady = false;
			P2.T = task.pid;
			P2.time = task.delay;
		}
		else {
			steck.push(task);
		}
	}
	else if (task.type == 3) {
		if (P3.isReady) {
			P3.isReady = false;
			P3.T = task.pid;
			P3.time = task.delay;
		}
		else {
			steck.push(task);
		}
	}
}

void work_proc() {
	if (!P1.isReady) {
		if (P1.time > 0)
			P1.time--;
		else {
			P1.isReady = true;
			done.push(P1.T);
			P1.T = 0;
		}
	}
	if (!P2.isReady) {
		if (P2.time > 0)
			P2.time--;
		else {
			P2.isReady = true;
			done.push(P2.T);
			P2.T = 0;
		}
	}
	if (!P3.isReady) {
		if (P3.time > 0)
			P3.time--;
		else {
			P3.isReady = true;
			done.push(P3.T);
			P3.T = 0;
		}
	}
}

void check_proc_stack() {
	Task t = steck.top();
	if (t.type == 1) {
		if (P1.isReady) {
			P1.isReady = false;
			P1.T = t.pid;
			P1.time = t.delay;
			steck.pop();
		}
	}
	else if (t.type == 2) {
		if (P2.isReady) {
			P2.isReady = false;
			P2.T = t.pid;
			P2.time = t.delay;
			steck.pop();
		}
	}
	else if (t.type == 3) {
		if (P3.isReady) {
			P3.isReady = false;
			P3.T = t.pid;
			P3.time = t.delay;
			steck.pop();
		}
	}
}

void simulation() {
	do {
		if (_kbhit())//для работы цикла пока не нажмем "esc"
			if (_getch() == 0x1B) break;	//		

		generator(); //генерируем задачу, с разным интервалом времени, эмулируя работу очереди
		check_proc();//проверка процессоров на занятость
		work_proc();//работа процессоров
		if (!steck.empty())//проверка стека
			check_proc_stack();//проверка процессоров на занятость
		work_time++;
		update_screen();//обновляем экран
	} while (1);
}

int main() {
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	init();
	simulation();
}