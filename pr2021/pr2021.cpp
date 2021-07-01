#include "pch.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include "Task.h"
#include "windows.h"
#include "Processor.h"
#include <stack> 

#define separator "+------------------------------------------+\n"

Processor P1; //Процессор P1
Processor P2; // P2
Processor P3; // P3

int work_time;//время работы системы
int latency;//задержка генерации задач

Task task; //задача
std::stack <Task> steck;//стек
std::stack <Task> done;//массив с выполнеными задачами

int shet(int x) { //функция счета цифр в числе
	int n = 1;
	while ((x /= 10) > 0) n++;
	return n;
}

void print_dynamic(std::stack<Task> st) { //отображение выполненных задач
	int c = 0;
	if (st.empty() == false) {
		std::cout << "+-";
		for (std::stack<Task> temp = st; !temp.empty(); temp.pop(), c++) {
			if (c == 5) break;
			if (shet(temp.top().pid)==1)
				std::cout << " 00" << temp.top().pid << "(" << temp.top().type << ")";
			else if (shet(temp.top().pid)==2)
				std::cout << " 0" << temp.top().pid << "(" << temp.top().type << ")";
			else if (shet(temp.top().pid)==3)
				std::cout << " " << temp.top().pid << "(" << temp.top().type << ")";
		}
		if (st.size() == 1) std::cout << " ---------------------------------+\n";
		else if (st.size() == 2) std::cout << " --------------------------+\n";
		else if (st.size() == 3) std::cout << " -------------------+\n";
		else if (st.size() == 4) std::cout << " ------------+\n";
		else if (st.size() == 5) std::cout << " -----+\n";
		else std::cout << " ... -+\n";
	}
	else std::cout << separator;
}

void print_task(int t, int type) { //отображение задачи выбранного процессора(3 варианта, зависит от количетсва цифр в числе)
	if (shet(t)==1)
		std::cout << "+----------- Процессор P"<< type <<": 00" << t << " ------------+\n";
	else if (shet(t)==2)
		std::cout << "+----------- Процессор P"<< type <<": 0" << t << " ------------+\n";
	else if (shet(t)==3)
		std::cout << "+----------- Процессор P"<< type <<": " << t << " ------------+\n";
}

void print_work_time() {
	if (shet(work_time) == 1)
		std::cout << "+-------------------- " << work_time << " -------------------+\n";
	else if (shet(work_time) == 2)
		std::cout << "+-------------------- " << work_time << " ------------------+\n";
	else if (shet(work_time) == 3)
		std::cout << "+-------------------- " << work_time << " -----------------+\n";
}
	
void print() { //функция отображения симуляции
	print_work_time();
	std::cout << separator;
	print_task(P1.task.pid, 1);
	print_task(P2.task.pid, 2);
	print_task(P3.task.pid, 3);
	std::cout << separator;
	std::cout << "+------------------ Стек: -----------------+\n";
	print_dynamic(steck);
	std::cout << separator;
	std::cout << "+---------------- Выполнено: --------------+\n";
	print_dynamic(done);
	std::cout << separator;
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
	P1 = Processor(1, true, 0, 0);
	P2 = Processor(2, true, 0, 0);
	P3 = Processor(3, true, 0, 0);
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
			P1.task.pid = task.pid;
			P1.task.delay = task.delay;
		}
		else {
			steck.push(task);
		}
	}
	else if (task.type == 2) {
		if (P2.isReady) {
			P2.isReady = false;
			P2.task.pid = task.pid;
			P2.task.delay = task.delay;
		}
		else {
			steck.push(task);
		}
	}
	else if (task.type == 3) {
		if (P3.isReady) {
			P3.isReady = false;
			P3.task.pid = task.pid;
			P3.task.delay = task.delay;
		}
		else {
			steck.push(task);
		}
	}
}

void work_proc() {
	if (!P1.isReady) {
		if (P1.task.delay > 0)
			P1.task.delay--;
		else {
			P1.isReady = true;
			done.push(P1.task);
			P1.task.pid = 0;
		}
	}
	if (!P2.isReady) {
		if (P2.task.delay > 0)
			P2.task.delay--;
		else {
			P2.isReady = true;
			done.push(P2.task);
			P2.task.pid = 0;
		}
	}
	if (!P3.isReady) {
		if (P3.task.delay > 0)
			P3.task.delay--;
		else {
			P3.isReady = true;
			done.push(P3.task);
			P3.task.pid = 0;
		}
	}
}

void check_proc_stack() {
	Task t = steck.top();
	if (t.type == 1) {
		if (P1.isReady) {
			P1.isReady = false;
			P1.task.pid = t.pid;
			P1.task.delay = t.delay;
			steck.pop();
		}
	}
	else if (t.type == 2) {
		if (P2.isReady) {
			P2.isReady = false;
			P2.task.pid = t.pid;
			P2.task.delay = t.delay;
			steck.pop();
		}
	}
	else if (t.type == 3) {
		if (P3.isReady) {
			P3.isReady = false;
			P3.task.pid = t.pid;
			P3.task.delay = t.delay;
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