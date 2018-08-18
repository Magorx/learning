#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n = 100005;
vector<pair<long long, long long>> tree(n * 4 + 2);
long long inf = 1e18;
vector<long long> init_vector(n);

pair<long long, long long> build(int v, int l, int r) {
    if (r - l == 1) {
        return tree[v] = {init_vector[l], init_vector[l]};
    }
    int m = (l + r) / 2;
    pair<long long, long long> ret1 = build(2 * v + 1, l, m);
    pair<long long, long long> ret2 = build(2 * v + 2, m, r);
    return tree[v] = {min(ret1.first, ret2.first), max(ret1.second, ret2.second)};
}

pair<long long, long long> query(int v, int lv, int rv, int l, int r) {
    if (lv >= r || rv <= l) {
        return {+inf, -inf};
    } else if (lv >= l && rv <= r) {
        return tree[v];
    }
    int mv = (lv + rv) / 2;
    pair<long long, long long> ret1 = query(2 * v + 1, lv, mv, l, r);
    pair<long long, long long> ret2 = query(2 * v + 2, mv, rv, l, r);
    pair<long long, long long> ans = {min(ret1.first, ret2.first), max(ret1.second, ret2.second)};
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
    pair<long long, long long> ret1 = tree[2 * v + 1];
    pair<long long, long long> ret2 = tree[2 * v + 2];
    tree[v] = {min(ret1.first, ret2.first), max(ret1.second, ret2.second)};
}

int main() {
    int k = 0;
    cin >> k;
    for (int i = 0; i < (int)tree.size(); ++i) {
      tree[i] = {+inf, -inf};
    }
    for (long long i = 1; i < n; ++i) {
        init_vector[i] = (i * i) % 12345 + (i * i * i) % 23456;
    }
    build(1, 1, n);
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        if (x > 0) {
            pair <long long, long long> ret = query(1, 1, n, x, y + 1);
            cout << ret.second - ret.first << '\n';
        } else {
            x = abs(x);
            update(1, 1, n, x, y);
        }
    }
}