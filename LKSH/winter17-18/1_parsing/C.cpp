#include <iostream>
#include <string>
#include <vector>


const int Moroz = -30;
const int Ded_Moroz = 2018;
const int Snegurochka = 10;

const int mlen = 5;
const int dlen = 9;
const int slen = 11;
const int plen = 7;


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
  } else if (is_digit(cur_expr[cur_pos])) {
    cur_result = read_number(&cur_pos);
  } else if (char_in_string(cur_expr[cur_pos], "MDSP")) {
    if (cur_expr.substr(cur_pos, mlen) == "Moroz") {
      cur_pos += mlen;
      cur_result = Moroz;
    } else if (cur_expr.substr(cur_pos, dlen) == "Ded Moroz") {
      cur_pos += dlen;
      cur_result = Ded_Moroz;
    } else if (cur_expr.substr(cur_pos, slen) == "Snegurochka") {
      cur_pos += slen;
      cur_result = Snegurochka;
    } else if (cur_expr.substr(cur_pos, plen) == "Podarok") {
      cur_pos += plen;
      if (cur_expr[cur_pos] != '(') {
        wrong_expr = true;
      }
      cur_result = eval_unit(&cur_pos);
      if (cur_result > 0) {
        cur_result += 5;
      } else {
        cur_result *= -1;
      }
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
  long long result = evaluator.evaluate_expression(input);

  if (input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/' || input.length() == 1) {
    evaluator.wrong_expr = true;
  }
  for (int i = 0; i < input.length() - 1; ++i) {
    if (char_in_string(input[i], "+-*/") && char_in_string(input[i + 1], "+-*/")) {
      evaluator.wrong_expr = true;
    }
  }

  if (evaluator.wrong_expr) {
    std::cout << "WRONG\n";
  } else {
    std::cout << result << '\n';
  }
  return 0;
}
