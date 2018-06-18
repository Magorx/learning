#include <iostream>
#include <string>
#include <vector>


bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

long long read_number(std::string&expr, int* pos) {
  int cur_pos = *pos;
  long long n = 0;
  while (is_digit(expr[cur_pos])) {
    n = n * 10 + (expr[cur_pos] - '0');
    ++cur_pos;
  }
  *pos = cur_pos - 1;
  return n;
}

int main() {
  std::string input;
  std::cin >> input;
  for (int pos = 0; pos < input.length() - 1; ++pos) {
    if (is_digit(input[pos])) {
      int n = read_number(input, &pos);
      std::cout << n << '\n';
    } else {
      std::cout << input[pos] << '\n';
    }
  }
  return 0;
}
