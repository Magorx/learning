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

int32_t solution(std::string current_sequence, int32_t maximum_length, int32_t balance) {
    if (balance < 0 || balance > static_cast<int32_t>(maximum_length - current_sequence.length())) {
        return 0;
    }
    if (static_cast<int32_t>(current_sequence.length()) >= maximum_length) {
        if (RightBracketSequenceBalance(current_sequence)) {
            std::cout << current_sequence << '\n';
        }
    } else {
        solution(current_sequence + '(', maximum_length, balance + 1);
        solution(current_sequence + ')', maximum_length, balance - 1);
    }
    return 0;
}

int main() {
    int32_t sequence_length = 0;
    std::cin >> sequence_length;
    sequence_length *= 2;
    solution("", sequence_length, 0);
}