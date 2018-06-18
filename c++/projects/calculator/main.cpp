#include <iostream>
#include <vector>
#include <string>
#include "calculator.h"

int main() {
  std::cout << "Enter expression: ";
  std::string expression;
  std::getline(std::cin, expression);
  std::cout << "Result: " << calculate(expression) << '\n';
  return 0;
}