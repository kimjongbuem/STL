#include<iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cmath>
using namespace std;
size_t precedence(const char op) // ������ �켱���� ���Լ�
{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '^')
		return 3;
	throw runtime_error{ string{"invalid operator :"} +op };
}
double execute(stack<char>& ops, stack<double>&operands)
{
	double result = 0;
	double rhs = operands.top(); // ������ �����´�
	operands.pop(); //��������
	double lhs = operands.top(); //  ������ �����´�.
	operands.pop();

	switch (ops.top())
	{
	case '+':
		result = lhs + rhs;
		break;
	case '-':
		result = lhs - rhs;
		break;
	case '/':
		result = lhs / rhs;
		break;
	case '*':
		result = lhs * rhs;
		break;
	case '^':
		result = pow(lhs,rhs);
		break;
	default:
		throw runtime_error{ string{"invalid operator :"} +ops.top() };
	}
	ops.pop();
	operands.push(result);
	return result;
}
int main() {
	stack<double> operands; // �ǿ����� ����
	stack<char> operators; // ������ ����
	string exp; //�򰡽�
	cout << "An grithmetic expression can include the operaotrs +,-,*,/, and ^ for exponentiation" << endl<<endl;
	try {
		while (true) {
			cout << "ENTER an arithmetic expression and press Enter - enter and empty line to end." << endl;
			getline(cin, exp, '\n');
			if (exp.empty()) break;
			//������ �����Ѵ�.//
			exp.erase(remove(begin(exp), end(exp), ' '), end(exp));

			size_t index {  }; //���ڿ� ���� ���� �ε�����.
			// ��� ǥ���Ŀ��� �ǿ����ڴ� ���ڷ� �����ؾ��� // 
			operands.push(stod(exp, &index)); // ���ÿ� ù�� ° �ǿ����� ������, lhs�� �ִ´�.

			while (true) {
				operators.push(exp[index++]); // �����ڽ��ÿ� ������ �߰� ����
				//get rhs operand//
				size_t i = 0; // sub string idx
				operands.push(stod(exp.substr(index), &i)); // ������ �ǿ�����(rhs)�� �ִ´�.
				index += i;// ���� �ε����� ����...
				if (index == exp.length())  {//���� ���� �����Ͽ��ٸ�,
					while (!operators.empty())
						execute(operators, operands); //ó�������ʴ� ������ ����
					break;
				}
				// ������� �����ϸ� ó���� �����ڰ� ��������
				// ���� �����ڿ� ���ų� �� ���� �켱�����̸� �����Ѵ�.
				while (!operators.empty() && precedence(exp[index]) <= precedence(operators.top()))
					execute(operators, operands);
				}
				cout << "result = " << operands.top() << endl;
		}
	}
	catch(const exception& e){
		cerr << e.what() << endl;
	}
	cout << "calculate end.." << endl;
}