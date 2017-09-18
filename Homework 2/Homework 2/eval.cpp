#include <iostream>
#include <stack>
#include <string>
//#include <cassert>
using namespace std;

bool balanced(string expr)
{
	stack<char> pair;
	for (int i = 0; i < expr.size(); i++)
	{
		//if the current charact is an open symbol, push it in to the stack
		if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')
			pair.push(expr[i]);

		//if the current character is a closing symbol, 
		//compare it with the most recently entered open symbol, they should match
		//if the stack is empty, or the most recently entered open symbol doesn't match with the closing symbol
		//return false
		//return true only if the stack is empty because no open symbol is entered, or they all popped after matching with their "other half"
		if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}')
		{
			if (pair.empty())
				return false;
			else
			{
				char p = pair.top();
				switch (expr[i])
				{
				case ')':
					if (p == '(')
						pair.pop();
					else return false;
					break;
				case ']':
					if (p == '[')
						pair.pop();
					else return false;
					break;
				case '}':
					if (p == '{')
						pair.pop();
					else return false;
					break;
				}
			}
		}
	}

	return pair.empty();
}

//void test(int n)
//{
//	string s;
//	switch (n)
//	{
//	case 1:
//		s = "This class is CS 32 (Summer 2016)";
//		assert(balanced(s));
//		break;
//	case 2:
//		s = "John von Neumann (December 28, 1903 – February 8, 1957) was a great computer scientist.";
//		assert(balanced(s));
//		break;
//	case 3:
//		s = "(([[]{}]()))";
//		assert(balanced(s));
//		break;
//	case 4:
//		s = "Midterm I is on July 11th.";
//		assert(balanced(s));
//		break;
//	case 5:
//		s = "()[]";
//		assert(balanced(s));
//		break;
//	case 6:
//		s = "This class is important for many reasons.\n1) It is required for graduation for many majors.";
//		assert(!balanced(s));
//		break;
//	case 7:
//		s = ":-)";
//		assert(!balanced(s));
//		break;
//	case 8:
//		s = "(:";
//		assert(!balanced(s));
//		break;
//	case 9:
//		s = "([)]";
//		assert(!balanced(s));
//		break;
//	}
//}

int main()
{
	/*for (int n = 1; n <= 9; n++)
		test(n);
	cout << "Passed" << endl;*/
}