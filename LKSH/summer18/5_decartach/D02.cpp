#include <bits/stdc++.h>

using namespace std;

struct Node;
long long node_sum(Node* n);
long long node_max(Node* n);
long long node_min(Node* n);

const long long inf = 1e15;

struct Node{ 
  long long x;
  int y;
  long long s;
  long long size;
  long long max_v;
  long long min_v;
  Node* L;
  Node* R;

  Node(int x_) {
    x = x_;
    y = (rand() << 16) ^ rand();
    s = x_;
    L = nullptr;
    R = nullptr;
  }

  void update() {
    s = node_sum(L) + node_sum(R) + x;
    max_v = max(max(x, node_max(L)), node_max(L));
    min_v = min(min(x, node_min(L)), node_min(L));
  }
};

long long node_sum(Node* n) {
  if (!n) {
    return 0;
  } else {
    return n->s;
  }
}

long long node_min(Node* n) {
  if (!n) {
    return +inf;
  } else {
    return n->min_v;
  }
}

long long node_max(Node* n) {
  if (!n) {
    return -inf;
  } else {
    return n->max_v;
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

pair<Node*, Node*> split(Node* n, long long key) {
  if (!n) {
    return {nullptr, nullptr};
  }

  if (n->x <= key) {
    pair<Node*, Node*> ret = split(n->R, key);
    n->R = ret.first;
    n->update();
    return {n, ret.second};
  } else {
    pair<Node*, Node*> ret = split(n->L, key);
    n->L = ret.second;
    n->update();
    return {ret.first, n};
  }
}

Node* insert(Node* t, Node* new_node) {
  if (!t) return new_node;
  if (t->x == new_node->x) {
    return t;
  }

  if (new_node->y > t->y) {
    tie(new_node->L, new_node->R) = split(t, new_node->x);
    new_node->update();
    return new_node;
  } else {
    if (new_node->x > t->x) {
      t->R = insert(t->R, new_node);
      t->update();
    } else {
      t->L = insert(t->L, new_node);
      t->update();
    }
    return t;
  }
}

Node* del(Node* t, int value) {
  Node* ret1;
  Node* ret2;
  Node* ret3;
  tie(ret1, ret2) = split(t, value);
  tie(ret1, ret3) = split(ret1, value - 1);
  Node* merged = merge(ret1, ret2);
  return merged;
}

Node* find(Node* t, int value) {
  if (!t) {
    return nullptr;
  }
  if (t->x == value) {
    return t;
  }

  if (t->x > value) {
    return find(t->L, value);
  } else {
    return find(t->R, value);
  }
}

void print_tree(Node* n) {
  if (!n) {
    return;
  }

  print_tree(n->L);
  cout << n->x << ' ';
  print_tree(n->R);
}

long long sum(Node* t, long long l, long long r) {
  if (!t) {
    return 0;
  }

  if (t->max_v <= r && t->min_v >= l) {
    return t->s;
  }

  if (t->x > r) {
    return sum(t->L, l, r);
  } else if (t->x < l) {
    return sum(t->R, l, r);
  } else {
    return sum(t->L, l, r) + sum(t->R, l, r) + t->x;
  }
}

int main() {
  Node* tree = nullptr;
  int n = 0;
  cin >> n;

  char last_type = '!';
  long long last_sum = 0;
  while (n--) {
    char type;
    int value;
    cin >> type >> value;
    if (type == '+') {
      if (last_type == '?') {
        value = (last_sum + value) % 1000000000;
      }
      if (!find(tree, value)) {
        tree = insert(tree, new Node(value));
      }
    } else if (type == '?') {
      long long r;
      cin >> r;
      last_sum = sum(tree, value, r);
      cout << last_sum << '\n';
    } else {
      print_tree(find(tree, value));
      cout << '\n';
    }
    last_type = type;
  }

  return 0;
}