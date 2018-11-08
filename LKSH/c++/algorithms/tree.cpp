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
  if (add[v] != 0) {
    tree[2 * v + 1] += add[v];
    tree[2 * v + 2] += add[v];
    add[2 * v + 1] += add[v];
    add[2 * v + 2] += add[v];
    add[v] = 0;
  }
}

long long query(int v, int lv, int rv, int index) {
  if (rv - lv == 1) {
    push(v);
    return tree[v];
  }
  push(v);
  int mv = (lv + rv) / 2;
  if (index >= mv) {
    return query(2 * v + 2, mv, rv, index);
  } else if (index < mv){
    return query(2 * v + 1, lv, mv, index);
  }

  return 0;
}

void update_seg(int v, int lv, int rv, int l, int r, int delta) {
  push(v);
  if (lv >= r || rv <= l) {
    return;
  }
  if (lv >= l && rv <= r) { // main update section
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
  tree.resize(n * 4 + 2, 0);
  add.resize(n * 4 + 2, 0);
  init_vector.resize(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    cin >> init_vector[i];
  }
  build(0, 0, n);

  int k = 0;
  cin >> k;
  for (int i = 0; i < k; ++i) {
    char c;
    cin >> c;
    if (c == 'g') {
      int index = 0;
      cin >> index;
      --index;
      cout << query(0, 0, n, index) << '\n';
    } else {
      int from, to, delta;
      cin >> from >> to >> delta;
      --from;
      --to;
      update_seg(0, 0, n, from, to + 1, delta);
    }
  }

  return 0;
}