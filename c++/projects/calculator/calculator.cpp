#include "calculator.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>

#define DEBUG if (DEBUG_MODE)

const bool DEBUG_MODE = false;

const int32_t INVALID_INDEX = 0;

size_t IndexInStringByCharPtr(std::string string, char* charptr) {
  for (size_t i = 0; i < string.length(); ++i) {
    if (&string[i] == charptr) {
      return i;
    }
  }
  return -1;
}

double Calculated::eval() {
  std::cout << "ERROR, EVALING Calculated\n";
  return 0;
}

void Calculated::increase_eval_indexes() {
  std::cout << "ERROR, INCREASING Calculated INDEXES\n";
}

Number::Number(double number) {
  number_ = number;
  printable_form = std::to_string(number);
}

double Number::eval() {
  return number_;
}

Bracket::Bracket(std::vector<Calculated*>* expression_, size_t main_operator_index, bool opening) {
  printable_form = "(";
  expression = expression_;
  main_operator_index_ = main_operator_index;
  opening = opening;
}

void Bracket::set_pair_bracket(size_t index) {
  pair_bracket_index_ = index;
}

size_t& Bracket::get_main_operator_index() {
  return main_operator_index_;
}

double Bracket::eval() {
  if (static_cast<int32_t>(main_operator_index_) == INVALID_INDEX) {
    std::cout << "ERROR, BRACKET HAS INVALID INDEX \n";
  }
  return expression->at(main_operator_index_)->eval();
}

void Bracket::set_main_operator_index(size_t index) {
  main_operator_index_ = index;
}

void Bracket::increase_eval_indexes() {
  ++main_operator_index_;
}

Operator::Operator() {
  first_operand_ = 0;
  second_operand_ = 0;
}

Operator::Operator(std::vector<Calculated*>* expression_, size_t first_operand_index, size_t second_operand_index) {
  expression = expression_;
  first_operand_ = first_operand_index;
  second_operand_ = second_operand_index;
}

std::pair<size_t, size_t> Operator::get_operands_index() {
  return std::make_pair(first_operand_, second_operand_);
}

void Operator::increase_eval_indexes() {
  ++first_operand_;
  ++second_operand_;
}

Plus::Plus(std::vector<Calculated*>* expression_, size_t first_operand_index, size_t second_operand_index)
: Operator (expression_, first_operand_index, second_operand_index) {printable_form = "+";};

double Plus::eval() {
  return expression->at(first_operand_)->eval() + expression->at(second_operand_)->eval();
}

Minus::Minus(std::vector<Calculated*>* expression_, size_t first_operand_index, size_t second_operand_index)
: Operator (expression_, first_operand_index, second_operand_index) {printable_form = "-";};

double Minus::eval() {
  return expression->at(first_operand_)->eval() - expression->at(second_operand_)->eval();
}

Multiplicator::Multiplicator(std::vector<Calculated*>* expression_, size_t first_operand_index, size_t second_operand_index)
: Operator (expression_, first_operand_index, second_operand_index) {printable_form = "*";};

double Multiplicator::eval() {
  return expression->at(first_operand_)->eval() * expression->at(second_operand_)->eval();
}

Divider::Divider(std::vector<Calculated*>* expression_, size_t first_operand_index, size_t second_operand_index)
: Operator (expression_, first_operand_index, second_operand_index) {printable_form = "/";};

double Divider::eval() {
  return expression->at(first_operand_)->eval() / expression->at(second_operand_)->eval();
}

// TMP

void push_Calculated_into_expression(std::vector<Calculated*>* vector, Calculated* object, size_t pos) {
  if (pos >= vector->size()) {
    vector->push_back(object);
    return;
  }
  Calculated* prev = object;
  for (size_t i = pos; i < vector->size(); ++i) {
    Calculated* tmp = vector->at(i);
    std::string tmp_type = tmp->printable_form;
    if (tmp_type == "(" || tmp_type == "+" || tmp_type == "-" || tmp_type == "*" || tmp_type == "/") {
      tmp->increase_eval_indexes();
    }
    vector->at(i) = prev;
    prev = tmp;
  }
  vector->push_back(prev);
}

void insert_useful_things(std::vector<Calculated*>* expression) {
  Number* zero = new Number(0);
  Plus* plus = new Plus(expression, expression->size(), expression->size() + 2);
  expression->push_back(zero);
  expression->push_back(plus);
}

// ===== MAINWORK =====

std::vector<Calculated*>* ParceExpression(std::string input_expression) {
  std::vector<Calculated*>* expression = new std::vector<Calculated*>;
  std::vector<Bracket*> bracket_stack;
  Bracket* first_bracket = new Bracket(expression, 2, true);
  expression->push_back(first_bracket);
  insert_useful_things(expression);
  bracket_stack.push_back(first_bracket);

  for (size_t i = 0; i < input_expression.length(); ++i) {
    size_t expression_length = expression->size();
    char& symb = input_expression[i];
    Bracket* current_bracket = bracket_stack.back();

    if (current_bracket->get_main_operator_index() == INVALID_INDEX) {
      current_bracket->get_main_operator_index() = expression_length;
    }

    if (isdigit(symb)) {
      char* endptr;
      double readen_number = std::strtod(&input_expression[i], &endptr);
      i += endptr - &input_expression[i] - 1;
      Number* number = new Number(readen_number);
      expression->push_back(number);
    } else if (symb == '(') {
      Bracket* bracket = new Bracket(expression, expression_length + 2, true);
      bracket_stack.push_back(bracket);
      expression->push_back(bracket);
      insert_useful_things(expression);
    } else if (symb == ')') {
      bracket_stack.pop_back();
    } else if (symb == '+') {
      Plus* plus = new Plus(expression, current_bracket->get_main_operator_index(), expression_length + 1);
      expression->push_back(plus);
      current_bracket->get_main_operator_index() = expression_length;
    } else if (symb == '-') {
      Minus* minus = new Minus(expression, current_bracket->get_main_operator_index(), expression_length + 1);
      expression->push_back(minus);
      current_bracket->get_main_operator_index() = expression_length;
    } else if (symb == '*') {
      auto index_to_push = current_bracket->get_main_operator_index() + 1;
      if (expression_length  == index_to_push) {
        --index_to_push;
      }
      if (expression->at(index_to_push - 1)->printable_form == "*" || expression->at(index_to_push - 1)->printable_form == "/") {
        if (current_bracket->get_main_operator_index() == index_to_push - 1) {
          //current_bracket->set_main_operator_index(index_to_push + 1);
        }
        ++index_to_push;
      }
      Multiplicator* multiplicator = new Multiplicator(expression, index_to_push + 1, expression_length + 1);
      push_Calculated_into_expression(expression, multiplicator, index_to_push);
    } else if (symb == '/') {
      auto index_to_push = current_bracket->get_main_operator_index() + 1;
      if (expression_length  == index_to_push) {
        --index_to_push;
      }
      if (expression->at(index_to_push - 1)->printable_form == "*" || expression->at(index_to_push - 1)->printable_form == "/") {
        ++index_to_push;
      }
      Divider* divider = new Divider(expression, index_to_push + 1, expression_length + 1);
      push_Calculated_into_expression(expression, divider, index_to_push);
    }
  }
  return expression;
}

double calculate(std::string expression) {
  std::vector<Calculated*>* ready_to_calculate_expression = ParceExpression(expression);
  double result = ready_to_calculate_expression->at(0)->eval();
  
  for (size_t i = 0; i < ready_to_calculate_expression->size(); ++ i) {
    DEBUG std::cout << ready_to_calculate_expression->at(i)->printable_form << ' ';
    DEBUG std::cout << std::flush;
    delete ready_to_calculate_expression->at(i);
  }
  delete ready_to_calculate_expression;

  return result;
}
