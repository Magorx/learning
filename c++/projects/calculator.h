#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <vector>

class Calculated {
public:
  std::string printable_form;
  virtual double eval();
  virtual ~Calculated(){};
  virtual void increase_eval_indexes();
};

class Number : public Calculated {
  double number_;
public:
  Number(double number);
  double eval();
};

class Bracket : public Calculated {
  std::vector<Calculated*>* expression;
  size_t main_operator_index_;
  size_t pair_bracket_index_;
  bool opening;
public:
  Bracket(std::vector<Calculated*>* expression_, size_t main_operator_index, bool opening);
  void set_pair_bracket(size_t index);
  void set_main_operator_index(size_t index);
  void increase_eval_indexes();
  size_t& get_main_operator_index();
  double eval();
};

class Operator : public Calculated {
protected:
  std::vector<Calculated*>* expression;
  size_t first_operand_;
  size_t second_operand_;
public:
  Operator();
  Operator(std::vector<Calculated*>* expression_, size_t first_operand_index, size_t second_operand_index);
  std::pair<size_t, size_t> get_operands_index();
  void increase_eval_indexes();
};

class Plus : public Operator {
public:
  Plus(std::vector<Calculated*>* expression_, size_t first_operand_index, size_t second_operand_index);
  double eval();
};

class Minus : public Operator {
public:
  Minus(std::vector<Calculated*>* expression_, size_t first_operand_index, size_t second_operand_index);
  double eval();
};

class Multiplicator : public Operator {
public:
  Multiplicator(std::vector<Calculated*>* expression_, size_t first_operand_index, size_t second_operand_index);
  double eval();
};

class Divider : public Operator {
public:
  Divider(std::vector<Calculated*>* expression_, size_t first_operand_index, size_t second_operand_index);
  double eval();
};

std::vector<Calculated*>* ParceExpression(std::string input_expression);
double calculate(std::string expression);

#endif  // CALCULATOR_H INCLUDED