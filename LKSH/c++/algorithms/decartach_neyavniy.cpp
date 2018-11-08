#include <bits/stdc++.h>

using namespace std;

struct Node;
int size(Node* n);

struct Node { 
  int value;
  int key;
  int y;
  int s;
  Node* L;
  Node* R;

  Node(int value_) {
    value = value_;
    y = (rand() << 16) ^ rand();
    s = 1;
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
  }
};

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
  vector<Node*> arr;
  for (int i = 0; i < n; ++i) {
    int x = i + 1;
    arr.push_back(new Node(x));
  }

  stack<Node*> s;
  Node* tree = nullptr;
 
  for (int i = 0; i < n; ++i) {
    Node* cur_node = arr[i];
    Node* last_node = nullptr;
    while (!s.empty() && s.top()->y > cur_node->y) {
      last_node = s.top();
      last_node->update();
      s.pop();
    }
    if (s.empty()) {
        tree = cur_node;
        tree->update();
    }
    if (last_node) {
      if (!s.empty()) {
        s.top()->R = cur_node;
        s.top()->update();
      }
      cur_node->L = last_node;
      cur_node->update();
    } else {
      if (!s.empty()) {
        last_node = s.top();
        last_node->update();
        last_node->R = cur_node;
        last_node->update();
      }
    }
    s.push(cur_node);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    --l;
    if (!l) {
      continue;
    }

    Node* left_part;
    Node* middle_part;
    Node* right_part;

    tie(left_part, middle_part) = split(tree, l);
    tie(middle_part, right_part) = split(middle_part, r - l);

    left_part = merge(middle_part, left_part);
    tree = merge(left_part, right_part);
  }

  print_tree(tree);

  return 0;
}