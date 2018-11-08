#include "postfix.h"
#include "stack.h"
#include "iostream"
#include "vector"
#include <cctype>

void TPostfix::ToPostfix()
{
	if (CorrectRecord() == false)
		throw "error";
	TStack<char> op(infix.size());
	postfix = "";
	for (int i = 0; i < infix.size(); i++)
	{
		if (isalpha(infix[i]) || isdigit(infix[i]))
		{
			postfix += infix[i];
			while (isalpha(infix[i + 1]) || isdigit(infix[i + 1]))
			{
				postfix += infix[i + 1];
				i++;
			}
			postfix += ' ';
		}
		else
			if (infix[i] == '(')
				op.Push(infix[i]);
			else
				if (infix[i] == ')')
				{
					while (op.Back() != '(')
					{
						postfix += op.Pop();
						postfix += ' ';
					}
					op.Pop();
				}
				else
					if (op.IsEmpty() == true)
					{
						op.Push(infix[i]);
					}
					else
						if (Compare(infix[i]) <= Compare(op.Back()))
						{
							postfix += op.Pop();
							op.Push(infix[i]);
							postfix += ' ';
						}
						else
							op.Push(infix[i]);
	}
	while (op.IsEmpty() == false)
	{
		postfix += op.Pop();
		postfix += ' ';
	}
}

void TPostfix::SetInfix(string _infix)
{
	infix = _infix;
}

void TPostfix::Converter(string &str)
{
	string tmp;
	for (int i = 0; i < str.size(); i++)
	{
		if (IsOperand(str[i]))
		{
			cout << "Enter value " << str[i] << endl;
			cin >> tmp;
			char sym = str[i];
			int j = i;
			while (j < str.size())
			{
				if (sym == str[j])
				{
					str.erase(j, 1);
					str.insert(j, tmp);
					j += tmp.size();
				}
				else j++;
			}
		}
	}
}

double TPostfix::Calculate()
{
	Converter(postfix);
	TStack<double> value(postfix.size());
	string tmp;
	double tmp1;
	double tmp2;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] == ' ')
			continue;
		if (IsOperations(postfix[i]) == false)
		{
			while (postfix[i] != ' ')
			{
				tmp += postfix[i];
				i++;
			}
			value.Push(atof(tmp.c_str()));
			tmp = "";
		}
		if (IsOperations(postfix[i]) == true)
		{
			tmp1 = value.Pop();
			tmp2 = value.Pop();
			switch (postfix[i])
			{
			case '+':
				value.Push(tmp1 + tmp2);
				break;
			case '-':
				value.Push(tmp2 - tmp1);
				break;
			case '*':
				value.Push(tmp1*tmp2);
				break;
			case'/':
				value.Push(tmp2 / tmp1);
				break;
			}
		}
	}
	return value.Pop();
}

int TPostfix::Compare(char tmp1)
{
	if (tmp1 == '*' || tmp1 == '/')
		return 2;
	if (tmp1 == '-' || tmp1 == '+')
		return 1;
	if (tmp1 == '(')
		return 0;
}

bool TPostfix::CorrectRecord()
{
	int lb = 0, rb = 0;
	int operations = 0, operands = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
		{
			lb++;
			continue;
		}
		else if (infix[i] == ')')
		{
			rb++;
			continue;
		}
		if (rb > lb)
			return false;
		if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
			operations++;
		else
		{
			while (isalpha(infix[i + 1]) || isdigit(infix[i + 1]))
			{
				i++;
			}
			operands++;
		}
	}
	if ((IsOperations(infix[0]) == true || IsOperations(infix[infix.size() - 1]) == true))
		return false;
	if ((operands == operations + 1) && (lb == rb))
		return true;
	else return false;
}

bool TPostfix::IsOperations(char s)
{
	if (s == '+' || s == '-' || s == '*' || s == '/')
		return true;
	return false;
}
bool TPostfix::IsOperand(char s)
{
	if ((int(s) >= 65 && int(s) <= 90) || (int(s) >= 97 && int(s) <= 122))
		return true;
	return false;
}

