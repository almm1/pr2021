#include "pch.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include "Task.h"
#include "windows.h"
#include <stack> 

bool P1; //флаг готовности процессора P1
bool P2; // P2
bool P3; // P3

int T1=1; //id для задачи
int T2=10; //
int T3=100; //

int work_time;

Task task; //задача
std::stack <Task> steck;//стек

int shet(int x) { //функция счета цифр в числе
	int n = 1;
	while ((x /= 10) > 0) n++;
	return n;
}

void print_stack() { //отображение стека

}

void print_done() { //отображение выполненных задач

}

void print_task(int t, int type) { //отображение задачи выбранного процессора(3 варианта, зависит от количетсва цифр в числе)
	if (shet(t)==1)
		std::cout << "--- Процессор P"<< type <<": " << t << " -----\n";
	else if (shet(t)==2)
		std::cout << "--- Процессор P"<< type <<": " << t << " ----\n";
	else if (shet(t)==3)
		std::cout << "--- Процессор P"<< type <<": " << t << " ---\n";
}


void print() { //функция отображения симуляции
	std::cout << work_time;
	std::cout << "-------------------------\n";
	print_task(T1, 1);
	print_task(T2, 2);
	print_task(T3, 3);
	std::cout << "-------------------------\n";
	print_stack();
	print_done();
	std::cout << "-------------------------\n";
}

Task pop()
{
	int pid = 1 + rand() % 1000;
	int type = 1 + rand() % 3;
	int delay = 1 + rand() % 10;

	Task *task = new Task(pid, type, delay);
	return *task;
}

void init() {
	work_time = 0;
	P1 = false;
	P2 = false;
	P3 = false;
}



void simulation() {
	do {
		if (_kbhit())//для работы цикла пока не нажмем "esc"
		{							//
			int c = _getch();		//
			if (c == 0x1B) break;	//
		}							//
		work_time++;
		//T1++;/////////////////

		

		system("CLS");
		print();
		Sleep(1000);
	} while (1);
}

int main() {
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	init();
	simulation();
}