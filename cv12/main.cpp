#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <cmath>

std::unordered_map<char, int> operators = {
        {'+', 1}, {'-', 1}, {'~', 1},
        {'*', 2}, {'/', 2}, {'%', 2},
        {'^', 3},
        {'!', 3},
        {'(', -1}
};

std::string infix_to_postfix(const std::string & infix) {
    std::string postfix;
    std::stack<char> operator_stack;

    bool unary = true;

    for(char c : infix) {
        if(std::isspace(c)) {
            continue;
        }

        if(std::isdigit(c)) {
            postfix += c;
            unary = false;
        } else if(operators.count(c)) {
            if(unary && c == '-') {
                operator_stack.push('~');
            } else {
                while (!operator_stack.empty() && operators[c] <= operators[operator_stack.top()]) {
                    postfix += " ";
                    postfix += operator_stack.top();
                    operator_stack.pop();
                }
                postfix += " ";
                if(c == '!') {
                    postfix += "! ";
                    unary = false;
                    continue;
                } else {
                    operator_stack.push(c);
                }
            }
            unary = true;
        } else if (c == '(') {
            operator_stack.push(c);
            unary = true;
        } else if (c == ')') {
            while(operator_stack.top() != '(') {
                postfix += " ";
                postfix += operator_stack.top();
                operator_stack.pop();
            }
            operator_stack.pop();
            unary = false;
        }
    }

    while(!operator_stack.empty()) {
        postfix += " ";
        postfix += operator_stack.top();
        operator_stack.pop();
    }

    return postfix;
}

int evaluate(const std::string & postfix) {
    std::vector<std::string> tokens;
    std::stringstream ss(postfix);
    std::string temp;
    while(ss >> temp) {
        tokens.push_back(temp);
    }

    std::stack<int> numbers;

    for(const std::string & token : tokens) {
        if(std::isdigit(token[0])) {
            numbers.push(std::stoi(token));
            continue;
        }

        int num2 = numbers.top();
        numbers.pop();

        if(token == "~") {
            numbers.push(-num2);
            continue;
        } else if (token == "!") {
            int faktorial = 1;
            while(num2 > 1)
                faktorial *= num2--;
            numbers.push(faktorial);
            continue;
        }

        int num1 = numbers.top();
        numbers.pop();

        if(token == "+") {
            numbers.push(num1 + num2);
        } else if(token == "-") {
            numbers.push(num1 - num2);
        } else if(token == "*") {
            numbers.push(num1 * num2);
        } else if(token == "/") {
            numbers.push(num1 / num2);
        } else if(token == "%") {
            numbers.push(num1 % num2);
        } else if(token == "^") {
            numbers.push(pow(num1, num2));
        }
    }

    return numbers.top();
}

int main() {
    std::string infix = "(3 + 4)*2^ 3! - -6";

    std::string postfix = infix_to_postfix(infix);
    std::cout << postfix << std::endl;

    std::cout << evaluate(postfix);
    return 0;
}
