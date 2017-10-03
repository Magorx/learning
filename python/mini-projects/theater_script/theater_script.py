#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def leading_space_count(string):
    cnt = 0
    for symb in string:
        if symb == ' ':
            cnt += 1
        else:
            break
    return cnt


class ScriptExecuter(object):
    def __init__(self, tab_size=4):
        self.tab_size = tab_size

        self.vars = {'if_deep': 0, 'input': input}
        self.marks = []
        self.funcs = {'mark_exist': self.does_mark_exist,
                      'add_mark': self.add_mark}
        self.else_active_stack = []
        self.if_deep = 0

    def does_var_exist(self, var):
        return str(var in self.vars)

    def does_mark_exist(self, mark):
        return str(mark in self.marks)

    def add_mark(self, mark):
        self.marks.append(mark)
        return ''

    def add_var(self, var_name, var_value):
        var_value = self.get_value(var_value)
        self.vars[var_name] = var_value
        return ''

    def get_args_line(self, string, start_index):
        line = ''
        for symb_index in range(start_index, len(string)):
            symb = string[symb_index]
            if symb == ')':
                if line[-1] == '/':
                    line = line[:-1] + symb
                    continue
                else:
                    break
            line = line + symb
        return line

    def get_value(self, formula):
        spec_symbs = [' ', '$', '(', ')']
        delimiter_symbs = spec_symbs + [',', '/', '+', '-', '*', '#', '!', 
                                        '@', "'", '"', ';', ':', '.']
        if not formula:
            return ''
        formula = str(formula)
        init_formula = formula
        if formula[0] in spec_symbs and formula[0] != '$':
            formula = formula[1:]
        if formula[-1] in spec_symbs:
            formula = formula[:-1]
        if formula in self.vars:
            value = self.vars[formula]
            if callable(value):
                return str(value())
            else:
                return value

        var_name = ''
        collecting_var_name = False
        symb_index = 0
        while symb_index < len(formula):
            symb = formula[symb_index]
            if collecting_var_name:
                if symb not in delimiter_symbs:
                    var_name = var_name + symb
                if symb in delimiter_symbs:
                    formula = formula.replace('$' + var_name,  self.get_value(var_name))
                    symb_index = 0
                    collecting_var_name = False
                if symb_index == len(formula) - 1:
                    formula = formula.replace('$' + var_name,  self.get_value(var_name))
                    symb_index = 0
                    collecting_var_name = False

            if symb == '$':
                var_name = ''
                collecting_var_name = True
            symb_index += 1

        try:
            formula = str(eval(formula))
        except Exception:
            pass

        if len(formula) < 2:
            return formula
        if formula[0] in delimiter_symbs and init_formula[0] != formula[0]:
            formula = formula[1:]
        if formula[-1] in delimiter_symbs and init_formula[-1] != formula[-1]:
            formula = formula[:-1]

        return formula

    def execute_print(self, expr):
        expr = ' '.join(expr)
        start_index = expr.index('(') + 1
        print(self.get_value(self.get_args_line(expr, start_index)))

    def execute_assignment(self, expr):
        var_name, var_value = expr[0], ' '.join(expr[2:])
        if '$' in var_name:
            print('$ is NOT allowed in vars name')
            return None
        if var_value.startswith("'") and var_value.endswith("'"):
            self.vars[var_name] = var_value[1:-1]
        else:
            self.add_var(var_name, var_value)

    def execute_if(self, condition):
        condition = self.get_value(' '.join(condition))
        result = eval(condition)
        self.else_active_stack.append(not result)
        if result:
            self.if_deep += 1
        return result

    def execute_expr(self, expr):
        leading_space_cnt = leading_space_count(expr)
        expr = expr.lstrip(' ')
        expr = expr.split()
        if leading_space_cnt > self.if_deep  * self.tab_size:
            return 0

        if leading_space_cnt < self.if_deep  * self.tab_size:
            self.if_deep = leading_space_cnt / self.tab_size

        for func_name in self.funcs:
            while func_name in expr:
                index = expr.index(func_name)
                func = self.funcs[func_name]
                args_count = func.__code__.co_argcount
                args = expr[index + 1: index + args_count]
                result = func(*args)
                expr = expr[:index] + [result] + expr[index + args_count:]

            func = self.funcs[func_name]

        if '=' in expr:
            self.execute_assignment(expr)

        elif expr[0].startswith('print'):
            self.execute_print(expr)

        elif expr[0] == 'if':
            return self.execute_if(expr[1:])

        elif expr[0] == 'else' or expr[0] == 'finaly':
            else_active = self.else_active_stack.pop()
            if else_active:
                self.if_deep += 1
            return else_active

        return True

    def execute_script(self, script):
        for line in script.split('\n'):
            if not line:
                continue
            self.execute_expr(line)


def main():
    reader = ScriptExecuter()
    script = open('test.th', 'r').read()
    reader.execute_script(script)

if __name__ == "__main__":
    main()
