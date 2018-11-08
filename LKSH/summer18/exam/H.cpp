#include <bits/stdc++.h>

using namespace std;

struct Node;
long long size(Node* n);
long long node_gcd(Node* n);

struct Node { 
  long long value;
  long long key;
  long long cnt;
  long long y;
  long long s;
  long long max_gcd;
  Node* L;
  Node* R;

  Node(long long value_) {
    value = value_;
    y = (rand() << 16) ^ rand();
    s = 1;
    cnt = 1;
    max_gcd = value;
    L = nullptr;
    R = nullptr;
  }

  Node(long long value_, long long y_) {
    value = value_;
    y = y_;
    L = nullptr;
    R = nullptr;
  }

  void update() {
    s = size(L) + size(R) + 1;
    long long gcd_r = node_gcd(R);
    long long gcd_l = node_gcd(L);
    if (gcd_r == -1) {
      if (gcd_l == -1) {
        max_gcd = value;
      } else {
        max_gcd = __gcd(gcd_l, value);
      }
    } else {
      if (gcd_l == -1) {
        max_gcd = __gcd(gcd_r, value);
      } else {
        max_gcd = __gcd(__gcd(gcd_l, gcd_r), value);
      }
    }
  }
};

long long node_gcd(Node* n) {
  if (!n) {
    return -1;
  } else {
    return n->max_gcd;
  }
}

long long size(Node* n) {
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

pair<Node*, Node*> split(Node* n, long long key) {
  if (!n) {
    return {nullptr, nullptr};
  }

  if (n->value <= key) {
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
  if (t->value == new_node->value) {
    ++t->cnt;
    return t;
  }

  if (new_node->y > t->y) {
    tie(new_node->L, new_node->R) = split(t, new_node->value);
    return new_node;
  } else {
    if (new_node->value > t->value) {
      t->R = insert(t->R, new_node);
    } else {
      t->L = insert(t->L, new_node);
    }
    return t;
  }
}

Node* del(Node* t, long long value) {
  Node* ret1;
  Node* ret2;
  Node* ret3;
  tie(ret1, ret2) = split(t, value);
  tie(ret1, ret3) = split(ret1, value - 1);
  --ret3->cnt;
  if (ret3->cnt > 0) {
    return (merge(merge(ret1, ret3), ret2));
  } else {
    return merge(ret1, ret2);
  }
}

Node* find(Node* t, long long value) {
  if (!t) {
    return nullptr;
  }
  if (t->value == value) {
    return t;
  }

  if (t->value > value) {
    return find(t->L, value);
  } else {
    return find(t->R, value);
  }
}

Node* next(Node* t, long long value) {
  if (!t) {
    return nullptr;
  }

  if (t->value > value) {
      Node* ret = next(t->L, value);
      if (!ret) {
        return t;
      } else {
        return ret;
      }
  } else {
    return next(t->R, value);
  }
}

Node* prev(Node* t, long long value) {
  if (!t) {
    return nullptr;
  }

  if (t->value < value) {
      Node* ret = prev(t->R, value);
      if (!ret) {
        return t;
      } else {
        return ret;
      }
  } else {
    return prev(t->L, value);
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

int main() {
  long long n = 0;
  cin >> n;
  Node* tree = nullptr;
  for (long long i = 0; i < n; ++i) {
    char type;
    cin >> type;
    if (type == '+') {
      long long value = 0;
      cin >> value;
      tree = insert(tree, new Node(value));
    } else if (type == '?') {
      long long l, r;
      cin >> l >> r;
      --l;
      
      Node* left_part;
      Node* middle_part;
      Node* right_part;

      tie(left_part, middle_part) = split(tree, l);
      tie(middle_part, right_part) = split(middle_part, r);

      /*print_tree(left_part);
      cout << "| ";
      print_tree(middle_part);
      cout << "| ";
      print_tree(right_part);
      cout << '\n';*/
      if (!middle_part) {
        cout << 1 << '\n';
        tree = merge(left_part, right_part);
        continue;
      }

      cout << abs(node_gcd(middle_part)) << '\n';

      left_part = merge(left_part, middle_part);
      tree = merge(left_part, right_part);

    } else if (type == '-') {
      long long value;
      cin >> value;
      if (!find(tree, value)) {
        tree = insert(tree, new Node(value));
        continue;
      }
      tree = del(tree, value);
    } else {
      print_tree(tree);
      cout << '\n';
    }
  }

  return 0;
}