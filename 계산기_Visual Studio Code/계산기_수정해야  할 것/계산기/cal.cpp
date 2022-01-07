#include "cal.h"
#include<stdio.h>

double number[100];
char oper[100];
char enter[100];
char postfix[100];
int top1 = -1;
int top2 = -1;
double a = 0, b = 0, num = 0, p = 0;
char op;
int cnt = 1, j = 0, x = 0;

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

int Pow(int j) {
	int pow = 1;
	if (j == 0) {
		pow = 1;
		return pow;
	}

	for (int i = 0; i < j; i++) {
		pow = pow * 10;
	}
	return pow;
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
			num = num + (p - '0') * Pow(j);
			j++;
		}
		if (p == '#' || top1 == -1) break;
	}
	Numpush(num);
}

void PushPop() {
	if (cnt == 0) {
		Num();
		cnt++;
	}

	op = Operpop();
	b = Numpop();
	a = Numpop();
	Numpush(Calculator(a, b, op));
	postfix[x] = ' ';
	x++;
	postfix[x] = op;
	x++;
}

void MinusPushPop() {
	Numpop();
	if (number[top1] == '#') Numpop();
	Operpop();
	Numpush(-1);
	Numpush('#');
	Operpush('*');
}

void Oper(char enter) {
	while (1) {
		if (enter == '-' && (oper[top2] == '-' || oper[top2] == '+' || oper[top2] == '/' || oper[top2] == '*')) {
			if (number[top1] == '#') {
				Numpop();
				break;
			}
			PushPop();
		}//-
		else if (enter == '+' && (oper[top2] == '-' || oper[top2] == '+' || oper[top2] == '/' || oper[top2] == '*')) {
			PushPop();
		}//+
		else if (enter == '/' && (oper[top2] == '/' || oper[top2] == '*')) {
			PushPop();
		}///
		else if (enter == '*' && (oper[top2] == '/' || oper[top2] == '*')) {
			PushPop();
		}//*
		else break;
	}//while
}// Oper

void Rest() {
	while (1) {
		if (top2 != -1) {
			PushPop();
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
		postfix[x] = ' ';
		x++;
		postfix[x] = op;
		x++;
	}
}

void Minus(char enter) {
	while (1) {
		if (number[top1 - 1] == '#' && oper[top2 - 1] == '(') {
			MinusPushPop();
			break;
		}
		else if (number[top1] == '#' && oper[top2 - 1] == '(') {
			if (number[top1 - 1] != '#' && top1 != -1 && '0' <= enter && enter <= '9') break; //넘버스택에 # 또는 비어있지 않을 경우
			else if (oper[top2 - 1] == '(') break; // () 안에 a-b 식이 있을 경우
			else if (enter == ')') break; //()이후에 나온 경우
			else if ('0' <= enter && enter <= '9') break; //앞 문자열이 숫자인 경우

			MinusPushPop();
			break;
		}
		else if (oper[top2 - 1] == '(') break; // () 안에 a-b 식이 있을 경우
		else if (enter == ')') break; //()이후에 나온 경우
		else if ('0' <= enter && enter <= '9') break; //앞 문자열이 숫자인 경우

		MinusPushPop();
		break;
	}
	
}

void main() {
	printf("Enter =  ");
	scanf_s("%s", &enter, 100);

	for (int i = 0; enter[i]; i++) {
		Oper(enter[i]);

		if (enter[i] != '-' && enter[i] != '+' && enter[i] != '/' && enter[i] != '*' && enter[i] != '(' && enter[i] != ')') {
			Numpush(enter[i]);
			postfix[x] = enter[i];
			x++;
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
				postfix[x] = ' ';
				x++;
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
		printf("postfix = ");
		for(int i = 0; postfix[i]; i++) {
			printf("%c", postfix[i]);
		}
		printf("\n");
		
		printf("result = %0.3f\n", number[top1]);
	}
}