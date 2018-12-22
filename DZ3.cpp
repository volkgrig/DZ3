/* DZ3.cpp */
#include "pch.h"
#include <list>
#include <stack> 
#include <cmath>  
#include <string> 
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <process.h>

using namespace std;

#define PI       3.141592653589793238462643383279
#define INF      10000001
#define MIN_INF  0.00000000001
#define MAX_FACT 170
bool    fl_x                 = 0;
bool    fl_first_compilation = 1;

void callInstruction() {
	system("cls");
	cout <<
		"     ***Instruction***                                                       \n"   <<
		" Constants:                                                                  \n"   <<
		" PI = p                                                                      \n"   <<
		" Functions:                                                                  \n"   <<
		" sin()                                                                       \n"   <<
		" cos()                                                                       \n"   <<
		" tan()                                                                       \n"   <<
		" ctg()                                                                       \n"   <<
		" exp()                                                                       \n"   <<
		" asi() = arcsinus()                                                          \n"   <<
		" aco() = arccosinus()                                                        \n"   <<
		" ata() = arctangens()                                                        \n"   <<
		" act() = arccotangens()                                                      \n"   <<
		" All trigonometry function in degrees!                                       \n"   <<
		" 3!  = 1*2*3                                                                 \n"   <<
		" 1*(2+3) != 1(2+3)                                                           \n\n" <<
		" Количество вложенных функций в программе не ограничено программно           \n"   <<
		" Т.е sin(asi(sin(asi(sin(asi(sin(asi(sin(asi(sin(asi(sin(asi(0)))))))))))))) \n"   <<
		" будет работать корректно                                                    \n"   <<
		" Внутри сложных функций могу быть вложенные сложные функции                  \n"   <<
		" Факториал можно брать как от числа, так и от составного выражения           \n"   <<
		" Максимальный факториал 170!                                                 \n\n" ;
	cin.ignore();
	system("pause");
	system("cls");

}


void draw_imageError() {
	cout << "        \n" <<
		"   ()()     \n" <<
		"   (..)     \n" <<
		"  (' ')     \n" <<
		"  '' '' ";
}


int main();


void error(int code_mistake = -1) {
	cout << "\n";
	draw_imageError();
	switch (code_mistake) {
	case 1:  {cout << "Division by zero!                                         \n"; break; }
	case 2:  {cout << "Trigonometry function of this value does not exist!       \n"; break; }
	case 3:  {cout << "Too big value for factorial!                              \n"; break; }
	case 4:  {cout << "Float value. Factorial does not exist!                    \n"; break; }
	case 5:  {cout << "Negative value. Factorial does not exist!                 \n"; break; }
	case 6:  {cout << "False number of values!                                   \n"; break; }
	case 7:  {cout << "False operand!                                            \n"; break; }
	case 8:  {cout << "Not operands!                                             \n"; break; }
	case 9:  {cout << "False function!                                           \n"; break; }
	case 10: {cout << "False bracket!                                            \n"; break; }
	default: {cout << "Program mistake                                           \n"; break; }
	}
	if (code_mistake==9) { cin.ignore(); }
	cout << "Hm there's something wrong...  \n";
	system("pause");
	system("cls");
	cin.ignore();
	quick_exit(main());
}


struct Leksema
{
	char        type;
	long double value;
};


void    inputOpenBracket( char ch, int &fl_bin_unarn_minus, int &flag_bracket, int &fl_input_correct, int &kol_bracket_open,  stack <Leksema>& mystack, list <Leksema>& myqueue);
void    inputCloseBracket(         int &fl_bin_unarn_minus, int &flag_bracket, int &fl_input_correct, int &kol_bracket_close, stack <Leksema>& mystack, list <Leksema>& myqueue);
void    inputOperand(                       char   ch,                      stack <Leksema>& mystack, list <Leksema>& myqueue);
int     getRangOfOperand(                   char   ch                                                                        );
double  calculateSin(                                       double x                                                         );
double  calculateCos(                                       double x                                                         );
void    calculateTrigAndExpAndAddInStack(   char   fl_trig, double x_input, stack <Leksema>& mystack, list <Leksema>& myqueue);
char    check_and_switchTrigonometryAndExp( char   ch                                                                        );
void    inputFormula(                                                       stack <Leksema>& mystack, list <Leksema>& myqueue);
void    calculateOperForTwoArgsAndAddInStack(               double x_input, stack <Leksema>& mystack, list <Leksema>& myqueue);
bool    is_correctForTwoArguments(                                          stack <Leksema>  mystack, list <Leksema>  myqueue);
void    calculateFactAndAddInStack(                         double x_input, stack <Leksema>& mystack, list <Leksema>& myqueue);
double  calculateFormulaInPostfix(                          double x_input, stack <Leksema>  mystack, list <Leksema>  myqueue);
void    transform_toPostfix(                                                stack <Leksema>& mystack, list <Leksema>& myqueue);


void inputFormula( stack <Leksema>& mystack, list <Leksema>& myqueue) {
	char   ch;
	Leksema item;
	int flag_bracket       = 0;
	int  kol_bracket_open   = 0;
	int  kol_bracket_close  = 0;
	int  fl_input_correct   = 1;
	int  fl_bin_unarn_minus = 1;
	int  fl_callInstruction = 1;
	while (fl_callInstruction)
	{
		fl_input_correct = 1;
		ch = cin.peek();
		if (ch == '\n' ) break;
		if (ch == 'x') {
			cin >> ch;
			fl_x = 1;
			item.type = 0;
			item.value = INF;
			myqueue.push_back(item);
			fl_bin_unarn_minus = 0;
			continue;
		}
		if (ch == 'p') {
			cin >> ch;
			item.type  = 0;
			item.value = PI;
			myqueue.push_back(item);
			fl_bin_unarn_minus = 0;
			continue;
		}
		if (ch == 's' || ch == 'c' || ch == 't' || ch == 'e' || ch == 'a') {
			cin >> ch;
			char flag_function;
			flag_function  = check_and_switchTrigonometryAndExp(ch);
			if (flag_function == '0') { error(9); }
			inputOperand(flag_function, mystack, myqueue);
			flag_bracket = 1;
			inputOpenBracket('(', fl_bin_unarn_minus, flag_bracket, fl_input_correct, kol_bracket_open, mystack, myqueue);
			fl_bin_unarn_minus = 0;
		}
		if ((ch == '-' && fl_bin_unarn_minus) || ch == '.' || (ch >= '0' && ch <= '9'))
		{
			double x;
			cin >> x;
			item.type  = 0;
			item.value = x;
			myqueue.push_back(item);
			fl_bin_unarn_minus = 0;
			continue;
		}
		if (ch == '-' || ch == '+' || ch == '*' || ch == '/' || ch == '!')
		{
			cin >> ch;
			fl_input_correct = 0;
			inputOperand(ch, mystack, myqueue);
			if (ch != '!') { fl_bin_unarn_minus = 1; }
		}
		if (ch == '(')
		{
			cin >> ch;
			inputOpenBracket(ch, fl_bin_unarn_minus, flag_bracket, fl_input_correct, kol_bracket_open, mystack, myqueue);
		}
		if (ch == ')')
		{
			cin >> ch;
			inputCloseBracket(   fl_bin_unarn_minus,flag_bracket, fl_input_correct, kol_bracket_close, mystack, myqueue);
		}
		if (ch == 'i') {
			cin >> ch;
			Leksema item;
			item.type = ch;
			mystack.push(item);
			break;
		}
		if (fl_input_correct) { error(9); }
	}
}


void inputOperand(char ch, stack <Leksema>& mystack, list  <Leksema>& myqueue) {
	Leksema item;
	while (1)
	{
		int rang = 0;
		if (mystack.size() > 0) rang = getRangOfOperand(mystack.top().type);
		if (rang < getRangOfOperand(ch) || mystack.size() == 0)
		{
			item.type = ch;
			mystack.push(item);
			break;
		}
		myqueue.push_back(mystack.top());
		mystack.pop();
	}
}


void inputOpenBracket(char ch, int &fl_bin_unarn_minus, int &flag_bracket, int &fl_input_correct, int &kol_bracket_open, stack <Leksema>& mystack, list  <Leksema>& myqueue) {
	fl_input_correct = 0;
	Leksema item;
	item.type = ch;
	mystack.push(item);
	fl_bin_unarn_minus = 1;
	if (flag_bracket) {
		kol_bracket_open++;
	}
}


void inputCloseBracket(int &fl_bin_unarn_minus, int &flag_bracket, int &fl_input_correct, int &kol_bracket_close, stack <Leksema>& mystack,list  <Leksema>& myqueue ) {
	fl_input_correct = 0;
	if (flag_bracket) {
		kol_bracket_close++;
	}
	if (mystack.size() == 0)
	{
		error(6);
	}
	if (myqueue.size() == 0)
	{
		error(8);
	}
	bool flag = true;
	while (mystack.size() > 0) {
		if (mystack.top().type != '(')
		{
			myqueue.push_back(mystack.top());
			mystack.pop();
		}
		else {
			mystack.pop();
			flag = false;
			break;
		}

	}
	if (flag)
	{
		error(10);
	}

	fl_bin_unarn_minus = 0;
}


int getRangOfOperand(char ch)
{
	int rang = 0;
	if (ch == '+' || ch == '-'             ) rang = 1;
	if (ch == '*' || ch == '/'             ) rang = 2;
	if (ch == '1' || ch == '2' || ch == '3') rang = 3;
	if (ch == '4' || ch == '5' || ch == '6') rang = 3;
	if (ch == '7' || ch == '8' || ch == '9') rang = 3;
	if (ch == '!'                          ) rang = 3;
	return rang;
}


char check_and_switchTrigonometryAndExp(char ch1) {
	char ch2, ch3, ch4;
	char flag = '0';
	cin >> ch2;
	cin >> ch3;
	cin >> ch4;
	if ((ch1 == 's') && (ch2 == 'i') && (ch3 == 'n') && (ch4 == '(')) {
		flag =  '1';
	}
	if ((ch1 == 'c') && (ch2 == 'o') && (ch3 == 's') && (ch4 == '(')) {
		flag =  '2';
	}
	if ((ch1 == 't') && (ch2 == 'a') && (ch3 == 'n') && (ch4 == '(')) {
		flag =  '3';
	}
	if ((ch1 == 'c') && (ch2 == 't') && (ch3 == 'g') && (ch4 == '(')) {
		flag =  '4';
	}
	if ((ch1 == 'a') && (ch2 == 's') && (ch3 == 'i') && (ch4 == '(')) {
		flag =  '5';
	}
	if ((ch1 == 'a') && (ch2 == 'c') && (ch3 == 'o') && (ch4 == '(')) {
		flag =  '6';
	}
	if ((ch1 == 'a') && (ch2 == 't') && (ch3 == 'a') && (ch4 == '(')) {
		flag =  '7';
	}
	if ((ch1 == 'a') && (ch2 == 'c') && (ch3 == 't') && (ch4 == '(')) {
		flag =  '8';
	}
	if ((ch1 == 'e') && (ch2 == 'x') && (ch3 == 'p') && (ch4 == '(')) {
		flag =  '9';
	}
	return flag;
}


void transform_toPostfix( stack <Leksema>& mystack, list <Leksema>& myqueue) {
	if (myqueue.size() == 0) { error(8); }
	while (mystack.size() > 0)
	{
		myqueue.push_back(mystack.top());
		mystack.pop();
	}
}


double calculateFormulaInPostfix(double x_input, stack <Leksema> mystack, list <Leksema> myqueue) {
	for (list <Leksema>::iterator pos = myqueue.begin(); pos != myqueue.end(); ++pos) {
		if ((pos->value == INF) && fl_x) { pos->value = x_input; }
	}
	while (myqueue.size() > 0){
		if (myqueue.front().type == 0)
		{
			mystack.push(myqueue.front());
			myqueue.pop_front();
		}
		else
		{
			if (myqueue.front().type == '!') { calculateFactAndAddInStack(                            x_input, mystack, myqueue); continue; }
			if (myqueue.front().type == '1') { calculateTrigAndExpAndAddInStack(myqueue.front().type, x_input, mystack, myqueue); continue; }
			if (myqueue.front().type == '2') { calculateTrigAndExpAndAddInStack(myqueue.front().type, x_input, mystack, myqueue); continue; }
			if (myqueue.front().type == '3') { calculateTrigAndExpAndAddInStack(myqueue.front().type, x_input, mystack, myqueue); continue; }
			if (myqueue.front().type == '4') { calculateTrigAndExpAndAddInStack(myqueue.front().type, x_input, mystack, myqueue); continue; }
			if (myqueue.front().type == '5') { calculateTrigAndExpAndAddInStack(myqueue.front().type, x_input, mystack, myqueue); continue; }
			if (myqueue.front().type == '6') { calculateTrigAndExpAndAddInStack(myqueue.front().type, x_input, mystack, myqueue); continue; }
			if (myqueue.front().type == '7') { calculateTrigAndExpAndAddInStack(myqueue.front().type, x_input, mystack, myqueue); continue; }
			if (myqueue.front().type == '8') { calculateTrigAndExpAndAddInStack(myqueue.front().type, x_input, mystack, myqueue); continue; }
			if (myqueue.front().type == '9') { calculateTrigAndExpAndAddInStack(myqueue.front().type, x_input, mystack, myqueue); continue; }
			if (is_correctForTwoArguments(mystack, myqueue)) {calculateOperForTwoArgsAndAddInStack(   x_input, mystack, myqueue); continue; }
		}
	}
	if (mystack.size() == 0) {
		error(6);
	}
	return mystack.top().value;
}


void calculateFactAndAddInStack(double x_input, stack <Leksema>& mystack, list <Leksema>& myqueue) {
	if (mystack.size() == 0)
	{
		error(6);
	}
	double x, Rez;
	Rez = 1;
	x = mystack.top().value;
	mystack.pop();
	myqueue.pop_front();
	if (x > MAX_FACT) { error(3); }
	double fractional_part, whole_part;
	fractional_part = modf(x, &whole_part);
	if (fractional_part > MIN_INF) { error(4); }
	if (whole_part < 0) { error(5); }
	int x_int = (int)(whole_part);
	for (int i = 1; i < x_int + 1; i++) {
		Rez *= i;
	}
	Leksema item;
	item.type  = 0;
	item.value = Rez;
	mystack.push(item);
}


void calculateTrigAndExpAndAddInStack(char fl_trig, double x_input, stack <Leksema>& mystack, list <Leksema>& myqueue) {
	double x;
	x = mystack.top().value;
	mystack.pop();
	myqueue.pop_front();
	double Rez_trig;
	if (fl_trig == '1') { Rez_trig = calculateSin(x); }
	if (fl_trig == '2') { Rez_trig = calculateCos(x); }
	if (fl_trig == '3') {
		if (calculateCos(x) == 0) { error(2); }
		Rez_trig = tan(x*PI / 180.0);
		if (calculateSin(x) == 0) { Rez_trig = 0; }
	}
	if (fl_trig == '4') {
		if (calculateSin(x) == 0) { error(2); }
		Rez_trig = 1.0 / tan(x*PI / 180.0);
		if (calculateCos(x) == 0) { Rez_trig = 0; }
	}
	if (fl_trig == '5') {
		if ((x < -1) || (x > 1)) { error(2); }
		Rez_trig = asin(x)*180.0 / PI;
	}
	if (fl_trig == '6') {
		if ((x < -1) || (x > 1)) { error(2); }
		Rez_trig = acos(x)*180.0 / PI;
	}
	if (fl_trig == '7') { Rez_trig = atan(x)*180.0 / PI; }
	if (fl_trig == '8') { Rez_trig = atan(1.0 / x)*180.0 / PI; }
	if (fl_trig == '9') { Rez_trig = exp(x); }
	Leksema item;
	item.type  = 0;
	item.value = Rez_trig;
	mystack.push(item);
}


double calculateSin(double x) {
	double Rez_trig;
	Rez_trig = sin(x*PI / 180);
	double x_in_rad;
	double fractional_part;
	double whole_part_divison_180;
	fractional_part = modf(x / 180.0, &whole_part_divison_180);
	x = x - 180 * whole_part_divison_180;
	x_in_rad = x * PI / 180.0;
	if (x_in_rad == 0) { Rez_trig = floor(sin(PI)) / 10000000; }
	return Rez_trig;
}


double calculateCos(double x) {
	double Rez_trig;
	Rez_trig = cos(x*PI / 180);
	double x_in_rad;
	double fractional_part;
	double whole_part_divison_180;
	double whole_part_divison_90;
	fractional_part = modf(x / 180.0, &whole_part_divison_180);
	x = x - 180 * whole_part_divison_180;
	fractional_part = modf(x / 90.0,  &whole_part_divison_90);
	x_in_rad = x * PI / 180.0;
	if (abs(x_in_rad - PI * whole_part_divison_90 / 2) < MIN_INF && (x_in_rad != 0)) { Rez_trig = floor(cos(PI / 2)) / 10000000; }
	return Rez_trig;
}


bool is_correctForTwoArguments(stack <Leksema> mystack, list <Leksema> myqueue) {
	bool flagg = 1;
	if (mystack.size() == 0)
	{
		flagg = 0;
		error(6);
	}

	if (mystack.top().type)
	{
		flagg = 0;
		error(7);
	}
	if (mystack.size() - 1 == 0)
	{
		flagg = 0;
		error(6);
	}

	if (mystack.top().type)
	{
		flagg = 0;
		error(7);
	}
	if (myqueue.front().type == '/' && mystack.top().value == 0) {
		flagg = 0;
		error(1);

	}
	return flagg;
}


void calculateOperForTwoArgsAndAddInStack(double x_input, stack <Leksema>& mystack, list <Leksema>& myqueue) {
	double x, y, Rez;
	Leksema item;
	y = mystack.top().value;
	mystack.pop();
	x = mystack.top().value;
	mystack.pop();
	switch (myqueue.front().type)
	{
	case '+': {Rez = x + y; break; }
	case '-': {Rez = x - y; break; }
	case '*': {Rez = x * y; break; }
	case '/': {Rez = x / y; break; }
	default:
		error(7);
	}
	myqueue.pop_front();
	item.type  = 0;
	item.value = Rez;
	mystack.push(item);
}


void draw_imageAnswer() {
	cout <<
		"............................... \n" <<
		"... (((()-------------()))) ... \n" <<
		".......... \\_  @  _/ ..........\n" <<
		"............\\  I  / ...........\n" <<
		"............ {   } ............ \n" <<
		"............ {   } ............ \n" <<
		"............ /   \\ ............\n" <<
		"..........._/     \\_...........\n" <<
		"............................... \n" <<
		"............................... \n\n";
}


void printAnswer(double answer) {
	system("cls");
	draw_imageAnswer();
	cout << "Answer: " << answer << "\n";
	system("pause");
}


bool ask_for_getNewFormula() {
	system("cls");
	cout<<"One more formula? (y/n) \n";
	char ch;
	if (not fl_x) { cin.ignore(); }
	ch = cin.get();
	int flag_ask_for_getNewFormula = 0;
	if (ch == 'y') { flag_ask_for_getNewFormula = 1; }
	if (fl_x) { cin.ignore(); }
	return flag_ask_for_getNewFormula;
}


bool ask_for_getNewX() {
	system("cls");
	cout << "One more x? (y/n) \n";
	char ch;
	cin.ignore();
	ch = cin.get();
	int flag_ask_for_getNewX = 0;
	if (ch == 'y') { flag_ask_for_getNewX = 1; }
	return flag_ask_for_getNewX;
}


void calculateWithX(stack <Leksema> mystack, list <Leksema> myqueue) {
	double answer;
	double x_input = INF;
	bool   flag_ask_for_getNewX = 1;
	while (flag_ask_for_getNewX) {
		cout << "Enter value of x: \n";
		cin >> x_input;
		answer = MIN_INF;
		answer = calculateFormulaInPostfix(x_input, mystack, myqueue);
		if (answer != MIN_INF) { printAnswer(answer); }
		flag_ask_for_getNewX = ask_for_getNewX();
		if (answer != MIN_INF) { cin.ignore(); }
		system("cls");
	}
}


void draw_imageGoodbye() {
	system("cls");
	cout << "\n";
	cout <<
		" --------                   \n" <<
		" | Bye! |                   \n" <<
		" |       \\  /\\_/\\        \n" <<
		" ---------  |°s°|           \n" <<
		"            |''''\\_____/|  \n" <<
		"            |_|_|______)    \n" <<
		"            |_|_|...|_|_|   \n\n";
	system("pause");
}


int main()
{
	setlocale(LC_ALL, "RUS");
	if (fl_first_compilation) { callInstruction(); fl_first_compilation = 0; }
	int    flag_ask_for_getNewFormula = 1;
	double answer;
	while (flag_ask_for_getNewFormula) {
		fl_x = 0;
		answer = MIN_INF;
		system("cls");
		cout << "To call Instruction enter: i \n";
		cout << "Formula:                     \n";
		stack <Leksema> mystack;
		list  <Leksema> myqueue;
		double x_input      = INF;
		inputFormula(mystack, myqueue);
		if (mystack.size() > 0) {
			if (mystack.top().type == 'i') {
				mystack.pop();
				callInstruction();
				continue;
			}
		}
		if (mystack.size() == 0) { error(8); }
		transform_toPostfix(mystack, myqueue);
		if (fl_x) {
			calculateWithX( mystack, myqueue);
		}
		else {
			answer = calculateFormulaInPostfix(INF, mystack, myqueue);
			if (answer != MIN_INF) { printAnswer(answer); }
		}
		flag_ask_for_getNewFormula = ask_for_getNewFormula();
		if (answer != MIN_INF) { cin.ignore(); }
	}
	draw_imageGoodbye();
	return 0;
}
