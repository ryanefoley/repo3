/* File: shunting-yard.cpp
 *
 * An implementation of Dijkstra's shunting-yard algorithm for evaluating
 * infix expressions.
 */
 
#include <iostream>
#include <string>
#include "simpio.h"
#include "strlib.h"
#include "tokenscanner.h"
#include "stack.h"
using namespace std;

int evaluate(string& expression);

int main() {
	while (true) {
		string line = getLine("Enter an expression: ");
		cout << "That evaluates to " << evaluate(line) << endl;
	}
}

/* Given the stack of operators and operands, evaluates the topmost operator. */
void evaluateOneOperator(Stack<string>& operators, Stack<int>& operands) {
	string op = operators.pop();
	
	/* Note the order; the top of the stack is the right-hand side, and
	 * the second-to-top is the left-hand side.
	 */
	int rhs = operands.pop();
	int lhs = operands.pop();
	
	if (op == "+") {
		operands.push(lhs + rhs);
	} else if (op == "-") {
		operands.push(lhs - rhs);
	} else if (op == "*") {
		operands.push(lhs * rhs);
	} else if (op == "+") {
		operands.push(lhs + rhs);
	} else if (op == "/") {
		operands.push(lhs / rhs);
	} else if (op == "%") {
		operands.push(lhs % rhs);
	}
}

/* Returns the priority of a given operator. */
int priorityOf(string& op) {
	if (op == "+" || op == "-") return 0;
	if (op == "*" || op == "/" || op == "%") return 1;
	
	return -1;
}

int evaluate(string& expression) {
	TokenScanner scanner(expression);
	scanner.ignoreWhitespace();
	
	/* The operator and operand stacks. */
	Stack<int> operands;
	Stack<string> operators;
	
	while (scanner.hasMoreTokens()) {
		string token = scanner.nextToken();
		
		/* If the token is a number, it's an operand. */
		if (scanner.getTokenType(token) == NUMBER) {
			operands.push(stringToInteger(token));
		}
		/* Otherwise, it's an operator. */
		else {
			/* Keep evaluating operators until there are none left or the current
			 * operator has higher priority.
			 */
			while (!operators.isEmpty() && priorityOf(operators.top()) >= priorityOf(token)) {
				evaluateOneOperator(operators, operands);
			}
			
			/* Now, mark that we have to use this operator. */
			operators.push(token);
		}
	}
	
	/* Continuously process remaining operators. */
	while (!operators.isEmpty()) {
		evaluateOneOperator(operators, operands);
	}
	
	return operands.pop();
}
