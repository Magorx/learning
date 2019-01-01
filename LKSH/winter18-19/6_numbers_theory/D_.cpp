#include <bits/stdc++.h>

using namespace std;

long long RandLong(long long min, long long max) {
  if (max < min) {
    return 0;
  }
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<long long> dist(min, max);
  return dist(mt);
}

long long binmul(long long n, long long pow, long long mod) {
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

pair<long long, long long> odd_part_and_max_bin_power(long long n) {
  long long k = 0;
  while (n % 2 == 0) {
    n /= 2;
    k += 1;
  }
  return {n, k};
}

long long gcd(long long a, long long b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
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

bool compound(long long n, long long itters = 100) {
  if (n == 2) {
    return false;
  }
  if (n % 2 == 0) {
    return true;
  }

  auto ret = odd_part_and_max_bin_power(n - 1);
  long long odd = ret.first;
  long long k = ret.second;
  std::vector<long long> sdvig_result = sdvig(n - 1);
  long long s = sdvig_result[0];
  long long d = sdvig_result[1];
  assert(odd == d);
  assert(k == s);
  // cout << odd << ' ' << k << '\n';
  for (long long z = 0; z < itters; ++z) {
    long long random_number = RandLong(2ll, n - 1ll);
    long long cur_number = binpow(random_number, odd, n);
    if (cur_number == 1 || cur_number == n - 1) {
      continue;
    }
    bool flag = false;
    for (int i = 0; i < k - 1; ++i) {
      cur_number = binmul(cur_number, cur_number, n);
      if (cur_number == n - 1) {
        flag = true;
        break;
      } else if (cur_number == 1) {
        return true;
      }
    }
    if (flag) {
      continue;
    }
    return true;
  }
  return false;
}

bool f(long long n) {
  for (int i = 2; i < n; ++i) {
    if (n % i == 0) {
      return true;
    }
  }
  return false;
}

int main() {
  int k;
  cin >> k;
  for (int i = 0; i < k; ++i) {
    long long n = RandLong(10000000000000000, 100000000000000000);
    cout << n << ")" << endl;
    if (compound(n)) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
    }
  }
  return 0;
}