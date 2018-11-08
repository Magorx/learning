#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, m;

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> tree1;
vector<long long> tree2;
vector<long long> init_vector1;
vector<long long> init_vector2;

long long build(vector<long long>& tree, vector<long long>& init_vector, long long v, long long l, long long r) {
  if (r - l == 1) {
    return tree[v] = init_vector[l];
  }
  long long m = (l + r) / 2;
  tree[v] += build(tree, init_vector, 2 * v + 1, l, m);
  tree[v] += build(tree, init_vector, 2 * v + 2, m, r);
  return tree[v];
}

long long query(vector<long long>& tree, int v, int lv, int rv, int l, int r) {
  if (lv >= r || rv <= l) {
    return 0;
  }
  if (lv >= l && rv <= r) {
    return tree[v];
  }

  int mv = (lv + rv) / 2;
  long long ret1 = query(tree, 2 * v + 1, lv, mv, l, r);
  long long ret2 = query(tree, 2 * v + 2, mv, rv, l, r);
  return ret1 + ret2;
}

void update(vector<long long>& tree, int v, int lv, int rv, int index, int value) {
  if (lv > index || rv <= index) {
    return;
  }
  if (rv - lv == 1) { // main update section
    tree[v] = value;
    return;
  }
  long long mv = (lv + rv) / 2;
  update(tree, 2 * v + 1, lv, mv, index, value);
  update(tree, 2 * v + 2, mv, rv, index, value);
  tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

int main() {
  cin >> n;
  tree1.resize(n * 4 + 2, 0);
  tree2.resize(n * 4 + 2, 0);
  init_vector1.resize(n + 1, 0);
  init_vector2.resize(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    if (i % 2) {
      cin >> init_vector1[i];
    } else {
      cin >> init_vector2[i];
    }
  }

  build(tree1, init_vector1, 0, 0, n);
  build(tree2, init_vector2, 0, 0, n);

  int k = 0;
  cin >> k;
  for (int i = 0; i < k; ++i) {
    /*for (auto x : tree1) {
      cout << x << ' ';
    }
    cout << '\n';
    for (auto x : tree2) {
      cout << x << ' ';
    }
    cout << '\n';*/

    int c;
    cin >> c;
    if (c == 1) {
      int l, r;
      cin >> l >> r;
      if (l % 2 == 0) {
        cout << +query(tree1, 0, 0, n, l - 1, r) - query(tree2, 0, 0, n, l - 1, r) << '\n';
      } else {
        cout << -query(tree1, 0, 0, n, l - 1, r) + query(tree2, 0, 0, n, l - 1, r) << '\n';
      }
    } else {
      int index, value;
      cin >> index >> value; 
      if (index % 2 == 0) {
        update(tree1, 0, 0, n, index - 1, value);
      } else {
        update(tree2, 0, 0, n, index - 1, value);
      }
    }
  }

  return 0;
}
