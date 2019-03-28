#include<iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cmath>
using namespace std;
size_t precedence(const char op) // 연산자 우선순위 비교함수
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
	double rhs = operands.top(); // 우측값 가져온다
	operands.pop(); //스택제거
	double lhs = operands.top(); //  좌측값 가져온다.
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
	stack<double> operands; // 피연산자 스택
	stack<char> operators; // 연산자 스택
	string exp; //평가식
	cout << "An grithmetic expression can include the operaotrs +,-,*,/, and ^ for exponentiation" << endl<<endl;
	try {
		while (true) {
			cout << "ENTER an arithmetic expression and press Enter - enter and empty line to end." << endl;
			getline(cin, exp, '\n');
			if (exp.empty()) break;
			//공백을 제거한다.//
			exp.erase(remove(begin(exp), end(exp), ' '), end(exp));

			size_t index {  }; //문자열 식을 위한 인덱스임.
			// 모든 표현식에서 피연산자는 숫자로 시작해야해 // 
			operands.push(stod(exp, &index)); // 스택에 첫번 째 피연산자 좌측값, lhs를 넣는다.

			while (true) {
				operators.push(exp[index++]); // 연산자스택에 연산자 추가 ㄱㄱ
				//get rhs operand//
				size_t i = 0; // sub string idx
				operands.push(stod(exp.substr(index), &i)); // 우측값 피연산자(rhs)를 넣는다.
				index += i;// 식의 인덱스를 증가...
				if (index == exp.length())  {//식의 끝에 도달하였다면,
					while (!operators.empty())
						execute(operators, operands); //처리되지않는 연산자 실행
					break;
				}
				// 여기까지 도달하면 처리할 연산자가 남아있음
				// 이전 연산자와 같거나 더 높은 우선순위이면 실행한다.
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