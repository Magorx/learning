#include <bits/stdc++.h>
#include <string>

using namespace std;

struct MyInt {
  vector<int> val;
  int sign;

  MyInt() {
    sign = 1;
    val.resize(0);
  }

  MyInt(string s) {
    unsigned i = 0;
    if (s[0] == '-') {
      sign = -1;
      s = s.substr(1, s.size());
    } else {
      sign = 1;
    }
    reverse(s.begin(), s.end());
    val.resize(s.length());

    for (i = 0; i < s.length(); ++i) {
    val[i] = s[i] - '0';
    }
  }

  MyInt(int n) {
    *this = MyInt(to_string(n));
  }

  int size() const {
    return val.size();
  }

  void normalize() {
    int size = this->size();
    for (int i = 0; i < size - 1; ++i) {
      if (val[i] > 9) {
        val[i + 1] += val[i] / 10;
        val[i] %= 10;
      } else if (val[i] < 0) {
        while (val[i] < 0) {
        val[i + 1] -= 1;
        val[i] += 10;
        }
      }
    }
    while (abs(val[size - 1]) > 9) {
    if (val[size - 1] > 9) {
      val.push_back(0);
      val[size] += val[size - 1] / 10;
      val[size - 1] %= 10;
    } else if (val[size - 1] < 0) {
      sign = -1;
      val[size - 1] = val[size - 1] + 10;
    }
    size = this->size();
    }
  }

  void clear() {
    val.resize(0);
    sign = 1;
  }

  bool is_zero() const {
    for (auto i : val) {
    if (i) {
      return false;
    }
    }

    return true;
  }

  int to_int() {
    int n = 0;
    for (size_t i = 0; i < val.size(); ++i) {
    n *= 10;
    n += val[i];
    }
    return n;
  }

  string to_str() {
    string ret = "";
    if (is_zero()) {
      return "0";
    }
    if (sign < 0) {
        ret += '-';
    }
    bool was_not_zero = false;
    for (int i = size() - 1; i >= 0; --i) {
        if (was_not_zero || val[i]) {
          was_not_zero = true;
          ret += to_string(abs(val[i]));
        }
    }
    if (!was_not_zero) {
      ret = "0";
    }

    return ret;
  }
};

istream& operator>>(istream& input_stream, MyInt& myint)
{
  string s;
  input_stream >> s;

  unsigned i = 0;
  if (s[0] == '-') {
    myint.sign = -1;
    s = s.substr(1, s.size());
  } else {
    myint.sign = 1;
  }
  reverse(s.begin(), s.end());
  myint.val.resize(s.length());

  for (i = 0; i < s.length(); ++i) {
    myint.val[i] = s[i] - '0';
  }
  return input_stream;
}

ostream& operator<<(ostream& output_stream, const MyInt& myint)
{
  if (myint.is_zero()) {
  output_stream << 0;
  return output_stream;
  }
  if (myint.sign < 0) {
    cout << '-';
  }
  bool was_not_zero = false;
  for (int i = myint.size() - 1; i >= 0; --i) {
    if (was_not_zero || myint.val[i]) {
    was_not_zero = true;
    cout << abs(myint.val[i]);
    }
  }
  if (!was_not_zero) {
  cout << 0;
  }
  return output_stream;
}

bool operator<(const MyInt& first, const MyInt& second) {
  if (first.size() < second.size()) {
    return true;
  } else if (second.size() < first.size()){
    return false;
  } else {
    for (int i = first.size() - 1; i >= 0; --i) {
      if (first.val[i] < second.val[i]) {
        return true;
      } else if (first.val[i] > second.val[i]) {
        return false;
      }
    }
  }
  return false;
}

bool operator==(const MyInt& first, const MyInt& second) {
  if (first < second || second < first) {
    return false;
  } else {
    return true;
  }
}

MyInt operator+(const MyInt& first, const MyInt& second) {
  MyInt result;
  result.val.resize(max(first.size(), second.size()));
  for (int i = 0; i < min(first.size(), second.size()); ++i) {
    result.val[i] = first.val[i] * first.sign + second.val[i] * second.sign;
  }
  for (int i = min(first.size(), second.size()); i < max(first.size(), second.size()); ++i) {
    result.val[i] = max(first, second).val[i];
  }

  result.normalize();

  return result;
}

MyInt operator-(MyInt first, MyInt second) {
  MyInt result;
  if (first < second) {
  first.sign *= -1;
  result = first + second;
  result.sign *= -1;
  first.sign *= -1;
  } else if (second < first) {
  second.sign *= -1;
  result = first + second;
  second.sign *= -1;
  }
  return result;
}

MyInt operator*(const MyInt& first, int second) {
  MyInt result = first;
  for (int i = 0; i < first.size(); ++i) {
  result.val[i] *= second;
  }

  result.normalize();
  return result;
}

MyInt operator*(const MyInt& first, const MyInt& second) {
  MyInt result;
  result.clear();
  result.val.resize(first.size() * second.size());
  for (int i = second.size() - 1; i >= 0; --i) {
  result = result * 10;
  result = result + first * second.val[i];
  }

  result.normalize();
  return result;
}

MyInt operator/(MyInt first, const int second) {
  reverse(first.val.begin(), first.val.end());
  first.val.resize(first.size() + 1);
  reverse(first.val.begin(), first.val.end());
  MyInt result;
  if (first < second) {
  return to_string(0);
  }

  for (int i = first.size() - 1; i >= 1; --i) {
  // cout << i << ") " << first.val[i] << '\n';
  int cur_ans = first.val[i] / second;
  result.val.push_back(cur_ans);
  first.val[i - 1] += first.val[i] % second * 10;
  }
  reverse(result.val.begin(), result.val.end());

  return result;
}

int main() {
  MyInt n;
  cin >> n;

  MyInt l = 1;
  MyInt r = n;
  MyInt one("1");
  //cout << r << ' ' << l << ' ' << one << '\n';
  while (one.to_str() != (r - l).to_str()) {
    MyInt m = (l + r) / 2;
    MyInt mm = m * m;

    cout << l << ' ' << r << ' ' << m  << ' ' << n << ' ' << mm << '\n';

    while (*(mm.val.end() - 1) == 0) {
      mm.val.pop_back();
    }
    while (*(m.val.end() - 1) == 0) {
      m.val.pop_back();
    }
    /*for (int i = 0; i < mm.size(); ++i) {
      cout << mm.val[i];
    }
    cout << '\n' << mm.size() << '\n';*/
    if (n < mm) {
      r = m;
    } else {
      l = m;
    }
  }
  cout << l << '\n';

  return 0;
}