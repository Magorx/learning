#include <bits/stdc++.h>

using namespace std;

struct Node{ 
  int x;
  int y;
  Node* L;
  Node* R;

  Node(int x_) {
    x = x_;
    y = (rand() << 16) ^ rand();
    L = nullptr;
    R = nullptr;
  }
};

Node* merge(Node* L, Node* R) {
  if (!L) {
    return R;
  }
  if (!R) {
    return L;
  }

  if (L->y > R->y) {
    L->R = merge(L->R, R);
    return L;
  } else {
    R->L = merge(L, R->L);
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
    return {n, ret.second};
  } else {
    pair<Node*, Node*> ret = split(n->L, key);
    n->L = ret.second;
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
    return new_node;
  } else {
    if (new_node->x > t->x) {
      t->R = insert(t->R, new_node);
    } else {
      t->L = insert(t->L, new_node);
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
  return merge(ret1, ret2);
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

Node* next(Node* t, int value) {
  if (!t) {
    return nullptr;
  }

  if (t->x > value) {
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

Node* prev(Node* t, int value) {
  if (!t) {
    return nullptr;
  }

  if (t->x < value) {
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
  cout << n->x << ' ';
  print_tree(n->R);
}

int main() {
  int n = 0;
  cin >> n;
  Node* tree = nullptr;
  while (n --> 0) {
    int type;
    cin >> type;
    if (type == '+') {
      int value = 0;
      cin >> value;
      tree = insert(tree, new Node(value));
    } else if (type == '?') {
      int l, r;
      cin >> l >> r;
      --l;
      
      Node* left_part;
      Node* middle_part;
      Node* right_part;

      tie(left_part, middle_part) = split(tree, l);
      tie(middle_part, right_part) = split(middle_part, r);

      

      left_part = merge(middle_part, left_part);
      tree = merge(left_part, right_part);

    }
  }

  return 0;
}