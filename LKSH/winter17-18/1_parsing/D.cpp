#include <iostream>
#include <string>
#include <vector>
#include <map>


std::map<char, int> vars;


bool is_digit(char c) {
  return c >= '0' && c <= '9';
}


bool char_in_string(char c, std::string s) {
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == c) {
      return true;
    }
  }

  return false;
}


class Evaluator {
private:
  std::string cur_expr;
  long long eval_expr(int* pos);
  long long eval_term(int* pos);
  long long eval_factor(int* pos);
  long long eval_unit(int* pos);
  long long read_number(int* pos);

public:
  bool wrong_expr;
  long long evaluate_expression(const std::string& expr);
};

long long Evaluator::read_number(int* pos) {
  int cur_pos = *pos;
  long long n = 0;
  int first_is_zero = 2;
  while (is_digit(cur_expr[cur_pos])) {
    n = n * 10 + (cur_expr[cur_pos] - '0');
    ++cur_pos;
    if (first_is_zero == 2) {
      if (n == 0) {
        first_is_zero = 1;
      } else {
        first_is_zero = 0;
      }
    } else {
      if (first_is_zero) {
        wrong_expr = true;
      }
    }
  }
  *pos = cur_pos;
  return n;
}

long long Evaluator::evaluate_expression(const std::string& expr) {
  wrong_expr = false;
  cur_expr = expr;
  int pos = 0;
  long long result = eval_term(&pos);
  if (pos + 1 != expr.length()) {
    wrong_expr = true;
  }
  return result;
}

long long Evaluator::eval_expr(int* pos) {
  if (cur_expr[*pos] == ')') {
    wrong_expr = true;
  }
  return eval_term(pos);
}

long long Evaluator::eval_term(int* pos) {
  int cur_pos = *pos;
  long long cur_result = eval_factor(&cur_pos);
  while (cur_expr[cur_pos] == '+' || cur_expr[cur_pos] == '-') {
    long long tmp_result = 0;
    if (cur_expr[cur_pos] == '+') {
      ++cur_pos;
      tmp_result = eval_factor(&cur_pos);
      cur_result += tmp_result;
    } else {
      ++cur_pos;
      tmp_result = eval_factor(&cur_pos);
      cur_result -= tmp_result;
    }
  }

  *pos = cur_pos;
  return cur_result;
}


long long Evaluator::eval_factor(int* pos) {
  int cur_pos = *pos;
  long long cur_result = eval_unit(&cur_pos);
  while (cur_expr[cur_pos] == '*' || cur_expr[cur_pos] == '/') {
    long long tmp_result = 0;
    if (cur_expr[cur_pos] == '*') {
      ++cur_pos;
      tmp_result = eval_unit(&cur_pos);
      cur_result *= tmp_result;
    } else if (cur_expr[cur_pos] == '/') {
      ++cur_pos;
      tmp_result = eval_unit(&cur_pos);
      cur_result /= tmp_result;
    }
  }

  *pos = cur_pos;
  return cur_result;
}

long long Evaluator::eval_unit(int* pos) {
  int cur_pos = *pos;
  long long cur_result = 0;
  if (cur_expr[cur_pos] == '(') {
    ++cur_pos;
    cur_result = eval_expr(&cur_pos);
    ++cur_pos;
  } else if (cur_expr[cur_pos] == '%') {
    cur_result = read_number(&cur_pos);
  } else if (cur_expr[cur_pos] == '^') {
    ++cur_pos;
    cur_result = eval_expr(&cur_pos);
    if (cur_result == 0) {
      cur_result = 1;
    } else {
      cur_result = 0;
    }
  } else {
    wrong_expr = true;
  }

  *pos = cur_pos;
  return cur_result;
}


int main() {
  std::string input;
  std::getline(std::cin, input);
  Evaluator evaluator;
  std::string expr;
  
  for (char i = 'A'; i <= 'Z'; ++i) {
    vars[i] = false;
  }

  int to_ignore = 0;
  for (int i = 0; i < input.length(); ++i) {
    if (input[i] == ' ') {
      to_ignore = 1;
    }
    if (to_ignore) {
      --to_ignore;
      continue;
    }
    
    if (input.substr(i, 2) == "OR") {
      expr += '+';
      to_ignore = 1;
    } else if (input.substr(i, 3) == "AND") {
      expr += '*';
      to_ignore = 2;
    } else if (input.substr(i, 3) == "NOT") {
      expr += "^";
      to_ignore = 2;
    } else if (input.substr(i, 4) == "TRUE") {
      expr += '1';
      to_ignore = 3;
    } else if (input.substr(i, 5) == "FALSE") {
      expr += "0";
      to_ignore = 4;
    } else if (input[i] >= 'A' && input[i] <= 'Z') {
      expr += '%';
      expr += input[i];
    } else {
      expr += input[i];
    }
  }

  // std::cout << expr;
  //evaluator.evaluate_expression(input);

  int n = 0;
  int m = 0;
  int k = 0;

  std::vector<std::vector<char>> map = ()

  return 0;
}
