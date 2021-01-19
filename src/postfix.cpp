// Copyright 2020 GHA Test Team
#include "postfix.h"
#define N 300


int number(std::string str, int i, int n) {
	int x = 0;
	while ((i != n) && (str[i] > 47 && str[i] < 58 || str[i] == '.')) {
		x = x * 10 + (str[i] - 48);
		i++;
	}
	return x;
}

int new_index(int i, int x) {
	int c = 0;
	if (x == 0) c = 1;
	while (x != 0) {
		x /= 10;
		c++;
	}
	return c;
}

int set_priority(char x) {
	if (x == '(') return 0;
	else if (x == ')') return 1;
	else if (x == '+' || x == '-') return 2;
	else if (x == '*' || x == '/') return 3;
}

bool check_symbol(char s) {
	if (s != '(' && s != ')' && s != '+' && s != '-' && s != '*' && s != '/')
		return true;
	else
		return false;
}

std::string delete_gaps(std::string str) {
	char result[N] = { '\0' };
	unsigned int str_len = str.length(), j = 0;
	for (unsigned int i = 0; i < str_len; i++) {
		if (str[i] != 32)
			result[j++] = str[i];
	}
	return std::string(result);
}

std::string infix2prefix(std::string str) {
	str = delete_gaps(str);
	MyStack<char> stack_operations(N);
  std::string RPN;
	unsigned int i = 0, str_len = str.length(), rpn_index = 0;
	while (i != str_len) {
		// if it's a number
		if (check_symbol(str[i])) {
			unsigned int cur_i = i;
			i += new_index(i, number(str, i, str_len));
			for (int j = cur_i; j < i; j++)
				RPN.insert(rpn_index++, 1, str[j]);
			RPN.insert(rpn_index++, 1, ' ');
		}
		else {
			if (stack_operations.isEmpty() || set_priority(str[i]) == 0 || (set_priority(str[i]) > set_priority(stack_operations.get()))) {
				stack_operations.push(str[i++]);
			}
			else {
				// if it's common operation
				if (set_priority(str[i]) != 1) {
					while (!stack_operations.isEmpty() && set_priority(stack_operations.get()) >= set_priority(str[i])) {
						RPN.insert(rpn_index++, 1, stack_operations.pop());
						RPN.insert(rpn_index++, 1, ' ');
					}
					stack_operations.push(str[i++]);
				}
				// if it's closing parenthesis
				else {
					while (!stack_operations.isEmpty() && set_priority(stack_operations.get()) != 0) {
						RPN.insert(rpn_index++, 1, stack_operations.pop());
						RPN.insert(rpn_index++, 1, ' ');
					}
					stack_operations.pop();
					i++;
				}
			}
		}
	}
	while (!stack_operations.isEmpty()) {
		RPN.insert(rpn_index++, 1, stack_operations.pop());
		RPN.insert(rpn_index++, 1, ' ');
	}
	char result[N] = { '\0' };
	for (unsigned int i = 0; i < rpn_index - 1; i++)
		result[i] = RPN[i];
	return std::string(result);
}
