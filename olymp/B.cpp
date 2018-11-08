#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Number {
    int32_t base;
    std::vector<int32_t> digits;

    Number() {
        base = 10;
        digits = std::vector<int32_t>(1, 0);
    }

    Number(int32_t base_, int32_t decimal) {
        base = base_;
        while (decimal != 0) {
            digits.push_back(decimal % base);
            decimal /= base;
        }
        if (digits.size() == 0) {
            digits.push_back(0);
        } else {
            std::reverse(digits.begin(), digits.end());
        }
    }

    Number(int32_t decimal) {
        Number new_number = Number(10, decimal);
        base = new_number.base;
        digits = new_number.digits;
    }

    int32_t get_decimal_value() {
        int32_t result = 0;
        int32_t factor = 1;
        for (size_t i = 0; i < digits.size(); ++i) {
            result += factor * digits[digits.size() - 1 - i];
            factor *= base;
        }
        return result;
    }

    void convert_to_decimal() {
        Number new_number = Number(10, this->get_decimal_value());
        base = new_number.base;
        digits = new_number.digits;
    }

    void convert_to(int32_t base) {
        this->convert_to_decimal();
        *this = Number(base, this->get_decimal_value());
    }
};

std::ostream& operator<<(std::ostream& output_stream, const Number& number) {
    for (size_t i = 0; i < number.digits.size(); ++i) {
        if (number.digits[i] < 9) {
            output_stream << number.digits[i];
        } else {
            output_stream << char('A' - 10 + number.digits[i]);
        }
    }
    return output_stream;
}

std::istream& operator>>(std::istream& input_stream, Number& number) {
    int32_t input_number = 0;
    input_stream >> input_number;

    number.base = 10;
    number.digits = Number(10, input_number).digits;

    return input_stream;
}

int main()
{
    Number number;
    std::cin >> number;
    number.convert_to(2);
    std::reverse(number.digits.begin(), number.digits.end());
    std::cout << number << '\n';
    
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; ++i) {
      Number a;
      cin >> a;
      a.convert_to(2);
      for (int j = 0; j < a.digits.size(); ++j) {
        if (a.digits[j] == 1) {
          arr[i] += 1;
        } 
      }
    }

  int l = 0;
  int r = 1;

  int s = arr[0] + arr[1];

  while (r < n || l < n - 1) {
    
  }

  return 0;
}
