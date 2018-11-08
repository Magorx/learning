#include <bits/stdc++.h>

using namespace std;

struct Node;
int size(Node* n);
int node_gcd(Node* n);

struct Node { 
  int value;
  int key;
  int y;
  int s;
  long long max_gcd;
  Node* L;
  Node* R;

  Node(int value_) {
    value = value_;
    y = (rand() << 16) ^ rand();
    s = 1;
    max_gcd = value;
    L = nullptr;
    R = nullptr;
  }

  Node(int value_, int y_) {
    value = value_;
    y = y_;
    L = nullptr;
    R = nullptr;
  }

  void update() {
    s = size(L) + size(R) + 1;
    max_gcd = __gcd(__gcd(node_gcd(L), node_gcd(R)), value);
  }
};

int node_gcd(Node* n) {
  if (!n) {
    return 1;
  } else {
    return n->max_gcd;
  }
}

int size(Node* n) {
  if (!n) {
    return 0;
  } else {
    return n->s;
  }
}

Node* merge(Node* L, Node* R) {
  if (!L) {
    return R;
  }
  if (!R) {
    return L;
  }

  if (L->y > R->y) {
    L->R = merge(L->R, R);
    L->update();
    return L;
  } else {
    R->L = merge(L, R->L);
    R->update();
    return R;
  }
}

pair<Node*, Node*> split(Node* n, int k) {
  if (!n) {
    return {nullptr, nullptr};
  }

  int l_size = size(n->L);
  if (l_size >= k) {
    auto ret = split(n->L, k);
    n->L = ret.second;
    n->update();
    return {ret.first, n};
  } else {
    auto ret = split(n->R, k - l_size - 1);
    n->R = ret.first;
    n->update();
    return {n, ret.second};
  }
}

void print_tree(Node* n) {
  if (!n) {
    return;
  }

  print_tree(n->L);
  cout << n->value << ' ';
  print_tree(n->R);
}

bool cmp(Node* first, Node* second) {
  if (first->key < second->key) {
    return true;
  } else {
    return false;
  }
}

int main() {
  int n, m = 0;
  cin >> n >> m;
  Node* tree = nullptr;

  for (int i = 0; i < m; ++i) {
    char type;
    cin >> type;
    if (type == '?') {
      int l, r;
      cin >> l >> r;
      --l;

      Node* left_part;
      Node* middle_part;
      Node* right_part;

      tie(left_part, middle_part) = split(tree, l);
      tie(middle_part, right_part) = split(middle_part, r - l);

      cout << node_gcd(middle_part) << '\n';

      left_part = merge(middle_part, left_part);
      tree = merge(left_part, right_part);
    } else {
      int value;
      cin >> value;
      tree = merge(tree, new Node(value));
    }
  }

  print_tree(tree);

  return 0;
}