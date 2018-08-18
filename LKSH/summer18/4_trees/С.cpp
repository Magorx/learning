#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long n;
vector<long long> tree;
vector<long long> init_vector;
vector<long long> add;

long long build(long long v, long long l, long long r) {
  if (r - l == 1) {
    return tree[v] = init_vector[l];
  }
  long long m = (l + r) / 2;
  build(2 * v + 1, l, m);
  build(2 * v + 2, m, r);
  return tree[v];
}

void push(long long v) {
  // cout << "VERTEX " << v << '\n';
  if (add[v] != 0) {
    // cout << '1' << endl;
    tree[2 * v + 1] += add[v];
    // cout << '2' << endl;
    tree[2 * v + 2] += add[v];
    // cout << '3' << endl;
    add[2 * v + 1] += add[v];
    // cout << '4' << endl;
    add[2 * v + 2] += add[v];
    // cout << '5' << endl;
    add[v] = 0;
    // cout << '6' << endl;  
  }
}

long long query(long long v, long long lv, long long rv, long long index) {
  if (rv - lv == 1) {
    push(v);
    return tree[v];
  }
  push(v);
  long long mv = (lv + rv) / 2;
  if (index >= mv) {
    return query(2 * v + 2, mv, rv, index);
  } else if (index < mv){
    return query(2 * v + 1, lv, mv, index);
  }

  return 0;
}

void update_seg(long long v, long long lv, long long rv, long long l, long long r, long long delta) {
  push(v);
  // cout <<  v << ' ' <<  lv<< ' '  <<  rv<< ' '  <<  l << ' ' <<  r << '\n';
  if (lv >= r || rv <= l) {
    // cout << "ouch\n";
    return;
  }
  if (lv >= l && rv <= r) {
    // cout << "add\n";
    tree[v] += delta;
    add[v] += delta;
    return;
  }
  long long mv = (lv + rv) / 2;
  update_seg(2 * v + 1, lv, mv, l, r, delta);
  update_seg(2 * v + 2, mv, rv, l, r, delta);
}

int main() {
  cin >> n;
  tree.resize(n * 8 + 2, 0);
  add.resize(n * 8 + 2, 0);
  init_vector.resize(n + 1, 0);
  for (long long i = 0; i < n; ++i) {
    cin >> init_vector[i];
  }
  build(0, 0, n);

  long long k = 0;
  cin >> k;
  for (long long i = 0; i < k; ++i) {
    char c;
    cin >> c;
    if (c == 'g') {
      long long index = 0;
      cin >> index;
      --index;
      cout << query(0, 0, n, index) << '\n';
    } else {
      long long from, to, delta;
      cin >> from >> to >> delta;
      --from;
      --to;
      update_seg(0, 0, n, from, to + 1, delta);
    }
  }

  return 0;
}