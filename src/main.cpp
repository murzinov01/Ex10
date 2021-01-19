// Copyright 2020 GHA Test Team
#include "postfix.h"


int main() {
  std::string str;
  std::cout << "Enter the string: ";
  std::getline(std::cin, str);
  std::cout << "Initial string: " << str << std::endl;
  std::string postfix_str = infix2postfix(str);
  std::cout << "Result: " << postfix_str << std::endl;
  return 0;
}
