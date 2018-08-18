#include <bits/stdc++.h>

using namespace std;

struct Node;
int node_size(Node* n);
int inf = 10000000;

struct Node{ 
  int x;
  int y;
  int size;
  Node* L;
  Node* R;

  Node(int x_) {
    x = x_;
    y = (rand() << 16) ^ rand();
    size = 1;
    L = nullptr;
    R = nullptr;
  }

  void update() {
    size = node_size(L) + node_size(R) + 1;
  }
};

int node_size(Node* n) {
  if (!n) {
    return 0;
  } else {
    return n->size;
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

Node* k_max(Node* t, int value) {
  if (!t) {
    cout << "!warning!\n";
    return nullptr;
  }
  // cout << "Node[" << t->x << "] size " << t->size << '\n';

  if (node_size(t->R) + 1 == value) {
    return t;
  }

  if (node_size(t->R) >= value) {
    return k_max(t->R, value);
  } else {
    return k_max(t->L, value - node_size(t->R) - 1);
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
  Node* tree = nullptr;
  int n = 0;
  cin >> n;

  while (n--) {
    int type, value;
    cin >> type >> value;
    if (type == 0) {
      cout << k_max(tree, value)->x << '\n';
    } else if (type == 1) {
      tree = insert(tree, new Node(value));
    } else if (type == -1) {
      tree = del(tree, value);
    } else {
      print_tree(find(tree, value));
      cout << '\n';
    }
  }

  return 0;
}