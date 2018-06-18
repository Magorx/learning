#include <bits/stdc++.h>

std::string halfed(std::string str) {
  std::string result;
  int a = str.length() / 2;
  if (str.length() % 2) {
    a++;
  }
  for (int i = 0; i < a; ++i) {
    result += str[i];
  }
  return result;
}

int main() {
  std::string n("1");
  while (true) {
    int l = n.length();
    int index = l / 2;
    if (l % 2) {
      index += 1;
    }
    if (index - 1 == l - index) {
      n[index] += 1;
      if (n[index] > '9') {
        n[index] = '0';
        n = halfed(n) + halfed(n);
      }
    } else {
      n[index] += 1;
      n[l - index] += 1;
      if (n[index] > '9') {
        n[index] = '0';
        n[l - index] = '0';
        n = halfed(n)
      }
    }

  }

  return 0;
}