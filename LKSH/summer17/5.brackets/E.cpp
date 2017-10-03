#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

bool RightBracketSequenceStack(std::string sequence) {
    std::stack<char> stack;
    for (char symbol : sequence) {
        if (symbol == ')' || symbol == ']' || symbol == '}') {
            if (!stack.empty()) {
                char poped = stack.top();
                stack.pop();
                if ((poped == '(' && symbol == ')') || (poped == '[' && symbol == ']') || (poped == '{' && symbol == '}')) {
                    continue;
                } else {
                    return false;
                    return 0;
                }
            } else {
                return false;
                return 0;
            }
        } else {
            stack.push(symbol);
        }
    }
    if (!stack.empty()) {
        return false;
    } else {
        return true;
    }
}

bool RightBracketSequenceBalance(std::string sequence) {
    int32_t balance = 0;
    for (char symbol : sequence) {
        if (symbol == '(' || symbol == '[' || symbol == '{') {
            ++balance;
        } else  if (symbol == ')' || symbol == ']' || symbol == '}') {
            --balance;
        }
    }
    if (balance == 0) {
        return true;
    } else {
        return false;
    }
}

std::string get_all(std::stack<char> stack) {
    std::string result;
    int32_t to_get = stack.size();
    for (int32_t i = 0; i < to_get; ++i) {
        result.push_back(stack.top());
        stack.pop();
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::string string;
    std::getline(std::cin, string);
    int32_t to_replace = 0;
    int32_t balance = 0;
    int32_t min_balance = 0;
    for (char symbol : string) {
        if (symbol == '(' || symbol == '[' || symbol == '{') {
            ++balance;
        } else  if (symbol == ')' || symbol == ']' || symbol == '}') {
            --balance;
        }
        if (balance < 0) {
            if (balance < min_balance) {
                min_balance = balance;
                ++to_replace;
            }
        }
    }
    if (balance != 0) {
        std::cout << -1 << '\n';
    } else {
        std::cout << (to_replace + 1) / 2 << '\n';
    }
}