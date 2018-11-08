#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string expression("a+b");
	TPostfix postfix;
	double res;
	setlocale(LC_ALL, "Russian");
	cout << "Введите арифметическое выражение: ";
	cin >> expression;
	cout << expression << endl;
	postfix.SetInfix(expression);
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	postfix.ToPostfix();
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	cout << "Выражение равно :" << postfix.Calculate() << endl;
	system("pause");
}
