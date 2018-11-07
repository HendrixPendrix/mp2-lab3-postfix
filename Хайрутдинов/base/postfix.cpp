#include "postfix.h"
#include "stack.h"
#include "iostream"
#include "vector"

void TPostfix::ToPostfix()
{
	if (CorrectRecord() == false)
		throw "error";
	TStack<char> op(infix.size());
	postfix = "";
	for (int i = 0; i < infix.size(); i++)
	{
		if (IsOperand(infix[i]) == true)
		{
			postfix += infix[i];
		}
		else
			if (infix[i] == '(')
				op.Push(infix[i]);
			else
				if (infix[i] == ')')
				{
					while (op.Back() != '(')
						postfix += op.Pop();
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
						}
						else
							op.Push(infix[i]);
	}
	while (op.IsEmpty() == false)
		postfix += op.Pop();
}

void TPostfix::SetInfix(string _infix)
{
	infix = _infix;
}

double TPostfix::Calculate()
{
	TStack<double> value(postfix.size());
	vector <double> nums;
	vector <char> sym;
	double tmp;
	double tmp1;
	double tmp2;
	bool flag = false;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (IsOperand(postfix[i]) == true)
		{
			for (int j = 0; j < sym.size(); j++)
				if (postfix[i] == sym[j])
				{
					value.Push(nums[j]);
					flag = true;
					break;
				}
			if (!flag)
			{
				sym.push_back(postfix[i]);
				cout << "Enter value " << postfix[i] << endl;
				cin >> tmp;
				nums.push_back(tmp);
				value.Push(tmp);
			}
			flag = false;
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
			operands++;
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

