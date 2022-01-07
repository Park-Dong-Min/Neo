#include "cal.h"
#include<stdio.h>

double number[100];
char oper[100];
char enter[100];
int arr[10] = { 1, 10, 100, 1000, 10000, 100000 };
int top1 = -1;
int top2 = -1;
double a = 0, b = 0, num = 0, p = 0;
char op;
int cnt = 1, j = 0, m = 0;

void Numpush(double num) {
	top1++;
	number[top1] = num;
}
void Operpush(char Oper) {
	top2++;
	oper[top2] = Oper;
}

double Numpop() {
	return number[top1--];
}

char Operpop() {
	return oper[top2--];
}

double Calculator(double a, double b, char op) {
	switch (op) {
	case '-':
		return a - b;
	case '+':
		return a + b;
	case '/':
		return a / b;
	case '*':
		return a * b;
	default: break;
	}
}//Calculator

void Num() {
	j = 0;
	num = 0;
	while (1) {
		p = Numpop();
		if (p != '#') {
			num = num + (p - '0') * arr[j];
			j++;
		}
		if (p == '#' || top1 == -1) break;
	}
	Numpush(num);
}

void Oper(char enter) {
	while (1) {
		if (enter == '-' && (oper[top2] == '-' || oper[top2] == '+' || oper[top2] == '/' || oper[top2] == '*')) {
			if (number[top1] == '#') {
				Numpop();
				break;
			}

			if (cnt == 0) {
				Num();
				cnt++;
			}

			op = Operpop();
			b = Numpop();
			a = Numpop();
			Numpush(Calculator(a, b, op));
		}//-
		else if (enter == '+' && (oper[top2] == '-' || oper[top2] == '+' || oper[top2] == '/' || oper[top2] == '*')) {
			if (cnt == 0) {
				Num();
				cnt++;
			}

			op = Operpop();
			b = Numpop();
			a = Numpop();
			Numpush(Calculator(a, b, op));
		}//+
		else if (enter == '/' && (oper[top2] == '/' || oper[top2] == '*')) {
			if (cnt == 0) {
				Num();
				cnt++;
			}

			op = Operpop();
			b = Numpop();
			a = Numpop();
			Numpush(Calculator(a, b, op));
		}///
		else if (enter == '*' && (oper[top2] == '/' || oper[top2] == '*')) {
			if (cnt == 0) {
				Num();
				cnt++;
			}

			op = Operpop();
			b = Numpop();
			a = Numpop();
			Numpush(Calculator(a, b, op));
		}
		else break;
	}//while
}// Oper

void Rest() {
	while (1) {
		if (top2 != -1) {
			if (cnt == 0) {
				Num();
				cnt++;
			}

			op = Operpop();
			b = Numpop();
			a = Numpop();
			Numpush(Calculator(a, b, op));
		}
		else break;
	}
}

void Par() {
	while (1) {
		if (cnt == 0) {
			Num();
			cnt++;
		}

		op = Operpop();
		if (op == '(') break;
		b = Numpop();
		a = Numpop();
		Numpush(Calculator(a, b, op));
	}
}

void Minus(char enter) {
	while (1) {
		if (number[top1 - 1] == '#' && oper[top2 - 1] == '(') {
			Numpop();
			if (number[top1] == '#') Numpop();
			Operpop();
			Numpush(-1);
			Numpush('#');
			Operpush('*');
			break;
		}
		else if (number[top1] == '#' && oper[top2 - 1] == '(') {
			if (number[top1 - 1] != '#' && top1 != -1 && '0' <= enter && enter <= '9') break; //넘버스택에 # 또는 비어있지 않을 경우
			else if (oper[top2 - 1] == '(') break; // () 안에 a-b 식이 있을 경우
			else if (enter == ')') break;
			else if ('0' <= enter && enter <= '9') break;

			Numpop();
			if (number[top1] == '#') Numpop();
			Operpop();
			Numpush(-1);
			Numpush('#');
			Operpush('*');
			break;
		}
		else if (oper[top2 - 1] == '(') break; // () 안에 a-b 식이 있을 경우
		else if (enter == ')') break;
		else if ('0' <= enter && enter <= '9') break;

		Numpop();
		Operpop();
		if (number[top1] == '#') Numpop();
		Numpush(-1);
		Numpush('#');
		Operpush('*');
		break;
	}
	
}

void main() {
	printf("Enter : \n");
	scanf_s("%s", &enter, 100);

	for (int i = 0; enter[i]; i++) {
		Oper(enter[i]);

		if (enter[i] != '-' && enter[i] != '+' && enter[i] != '/' && enter[i] != '*' && enter[i] != '(' && enter[i] != ')') {
			Numpush(enter[i]);
			cnt = 0;
		}
		else if (enter[i] == ')') {
			Par();
			cnt++;
		}
		else {
			if (cnt == 0) {
				Num();
				cnt++;
			}
			
			if (enter[i] != '(' && enter[i] != ')') {
				Numpush('#');
				Operpush(enter[i]);
			}
			else if (enter[i] == '(') {
				Operpush(enter[i]);
			}
		}

		if (enter[i] == '-' && number[top1] == '#') {
			Minus(enter[i-1]);
		}
	}

	Rest();	

	if (top1 == 0) {
		printf("result = %0.3f\n", number[top1]);
	}
}