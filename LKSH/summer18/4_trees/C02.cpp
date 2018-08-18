#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n = 100005;
vector<long long> tree(n * 4 + 2);
long long inf = 1e18;
vector<long long> init_vector(n);

long long build(int v, int l, int r) {
    if (r - l == 1) {
        return tree[v] = init_vector[l];
    }
    int m = (l + r) / 2;
    long long ret1 = build(2 * v + 1, l, m);
    long long ret2 = build(2 * v + 2, m, r);
    return tree[v] = {min(ret1.first, ret2.first), max(ret1.second, ret2.second)};
}

long long query(int v, int lv, int rv, int l, int r) {
    if (lv >= r || rv <= l) {
        return {+inf, -inf};
    } else if (lv >= l && rv <= r) {
        return tree[v];
    }
    int mv = (lv + rv) / 2;
    long long ret1 = query(2 * v + 1, lv, mv, l, r);
    long long ret2 = query(2 * v + 2, mv, rv, l, r);
    long long ans = {min(ret1.first, ret2.first), max(ret1.second, ret2.second)};
    return ans;
}

void update(int v, int lv, int rv, int index, int value) {
    // cout << v << '\n';
    if (rv - lv == 1) {
        // cout << v << '=' << value << '\n'; 
        tree[v] = {value, value};
        return;
    }
    int mv = (lv + rv) / 2;
    if (index >= mv) {
        update(2 * v + 2, mv, rv, index, value);
    } else if (index < mv){
        update(2 * v + 1, lv, mv, index, value);
    }
    long long ret1 = tree[2 * v + 1];
    long long ret2 = tree[2 * v + 2];
    tree[v] = {min(ret1.first, ret2.first), max(ret1.second, ret2.second)};
}

int main() {
  int m;
  cin >> n >> m;

  tree.resize(4 * n + 2, -inf);
  init.resize(n);

  for (int i = 0; i <  n; ++i) {
    cin >> init[i];
  }
  build(0, 0, n);
  cout << "max is " << maximum(0, 0, n, 0, n) << '\n';

  for (int i = 0; i < n; ++i) {
    int type, index, value;
    cin >> type >> index >> value;
    if (!type) {
      update(0, 0, n, index, value);
    } else {
      int l = index;
      int r = n;
      cout << "1-max = " << maximum(0, 0, n, l, r) << '\n';
      if (maximum(0, 0, n, l, r) < value) {
        cout << -1 << '\n';
        continue;
      }
      while (r - l != 1) {
        int m = (r + l) / 2;
        cout << "2-max = " << maximum(0, 0, n, l, m) << '\n';
        if (maximum(0, 0, n, l, m) >= value) {
          r = m;
        } else {
          l = m;
        }
      }
      cout << l << '\n';
    }
  }

  return 0;
}