#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    return 0;
}

bool isOperand(char c) {
    return isalnum(c); // Check if character is alphanumeric
}

string infixToRPN(const string& infix) {
    string rpn;
    stack<char> operators;

    for (char c : infix) {
        if (isspace(c))
            continue;
        if (isOperand(c)) {
            rpn += c;
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                rpn += operators.top();
                operators.pop();
            }
            if (!operators.empty() && operators.top() == '(')
                operators.pop(); // Discard the '('
        } else if (isOperator(c)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                rpn += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        rpn += operators.top();
        operators.pop();
    }

    return rpn;
}

int main() {
    string infix;
    cout << "Enter an infix expression: ";
    getline(cin, infix);

    string rpn = infixToRPN(infix);
    cout << "RPN expression: " << rpn << endl;

    return 0;
}
