#include <iostream>
#include <random>
#include <vector>

long long RandInt(long long min, long long max) {
  if (max < min) {
    return 0;
  }
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<long long> dist(min, max);
  return dist(mt);
}

long long binmul(long long n, long long pow, long long mod) {
  //std::cout << '=';
  if (pow == 1) {
    return n;
  } else if (pow == 0) {
    return 0;
  }  else {
    if (pow % 2 == 0) {
      long long a = binmul(n, pow / 2, mod) % mod;
      return (a + a) % mod;
    } else {
      return ((binmul(n, pow - 1, mod) % mod) + n % mod) % mod;
    }
  }
}

long long binpow(long long n, long long pow, long long mod) {
  if (pow == 1) {
    return n;
  } else if (pow == 0) {
    return 1;
  }  else {
    if (pow % 2 == 0) {
      long long a = binpow(n, pow / 2, mod) % mod;
      return binmul(a, a, mod) % mod;
    } else {
      return binmul((binpow(n, pow - 1, mod)), n % mod, mod);
    }
  }
}

std::vector<long long> sdvig(long long n) {
  long long s = 0;
  while (!(n % 2)) {
    ++s;
    n >>= 1;
  }
  return {s, n};
} 

bool miller(long long n) {
  if (n % 2 == 0) {
    return n == 2;
  } else if (n == 3) {
    return true;
  }

  std::vector<long long> sdvig_result = sdvig(n - 1);
  long long s = sdvig_result[0];
  long long d = sdvig_result[1];

  long long k = 1000;
  for (int i = 1; i < k; ++i) {
    bool flag = false;
    long long a = RandInt(2ll, n-3ll);
    long long x = binpow(a, d, n) % n;
    if (x == 1 || x == n - 1) {
      continue;
    } else {
      for (int r = 1; r <= s - 1; ++r) {
        x = binmul(x, x, n);
        if (x == 1) {
          return false;
        } else if (x == n - 1) {
          flag = true;
          break;
        }
      }
    }
    if (!flag) {
      return false;
    }
  }
  return true;
}

int main() {
  long long a = 0;
  std::cin >> a;
  if (miller(a)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}