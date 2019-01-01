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

bool compound(long long n, long long itters = 20) {
  if (n == 2) {
    return false;
  }
  if (n % 2 == 0) {
    return true;
  }

  auto ret = odd_part_and_max_bin_power(n - 1);
  long long odd = ret.first;
  long long k = ret.second;
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

template <typename T>
T gcd(T a, T b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

long long pretty_random(long long n, long long mod) {
  return (binmul(n, n, mod) + 2) % mod;
}

vector<long long> extermiante(long long n) {
  while (true) {
    long long x1 = RandLong(1, 11);
    long long x2 = pretty_random(x1, n);
    while (x1 != x2) {
      long long d = gcd(abs(x1 - x2), n);
      if (d != 1 && d != n) {
        return {d, n / d};
      }
      x1 = pretty_random(x1, n);
      x2 = pretty_random(pretty_random(x2, n), n);
    }
  }
}

int main() {
  long long n;
  cin >> n;
  auto res = extermiante(n);
  sort(res.begin(), res.end());
  cout << res[0] << " " << res[1] << '\n';

  return 0;
}