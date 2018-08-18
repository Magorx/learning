#include <bits/stdc++.h>

using namespace std;

struct Node;
int size(Node* n);
int node_min(Node* n);
int inf = 10000000;

struct Node{ 
  int value;
  int rev;
  int minimum;
  int y;
  int s;
  Node* L;
  Node* R;

  Node(int value_) {
    value = value_;
    y = rand();
    s = 1;
    rev = false;
    minimum = value_;
    L = nullptr;
    R = nullptr;
  }

  void reverse() {
    rev = !rev;
  }

  void push() {
    if (rev) {
      swap(L, R);
      if (L) {
        L->reverse();
      }
      if (R) {
        R->reverse();
      }
      rev = false;
    }
  }

  void update() {
    minimum = min(value, node_min(L));
    minimum = min(minimum, node_min(R));
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

int node_min(Node* n) {
  if (!n) {
    return +inf;
  } else {
    return n->minimum;
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
    L->push();
    L->R = merge(L->R, R);
    L->update();
    return L;
  } else {
    R->push();
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
    n->push();
    auto ret = split(n->L, k);
    n->L = ret.second;
    n->update();
    return {ret.first, n};
  } else {
    n->push();
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

  n->push();
  print_tree(n->L);
  cout << n->value << ' ';
  print_tree(n->R);
}

int main() {
  srand(time(NULL));
  int n, m = 0;
  cin >> n >> m;
  Node* tree = nullptr;
  for (int i = 0; i < n; ++i) {
    int x = 0;
    cin >> x;
    tree = merge(tree, new Node(x));
  }

  /*stack<Node*> s;
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
      cur_node->L = last_node;
      cur_node->update();
      if (!s.empty()) {
        s.top()->R = cur_node;
        s.top()->update();
      }
    } else {
      if (!s.empty()) {
        last_node = s.top();
        last_node->update();
        last_node->R = cur_node;
        last_node->update();
      }
    }
    s.push(cur_node);
  }*/

  for (int i = 0; i < m; ++i) {
    int type = -1;
    cin >> type;
    int l, r;
    cin >> l >> r;
    if (l == r) {
      if (type == 1) {
        continue;
      }
    }
    --l;

    Node* left_part;
    Node* middle_part;
    Node* right_part;
    tie(left_part, middle_part) = split(tree, l);
    tie(middle_part, right_part) = split(middle_part, r - l);

    /* print_tree(left_part);
    cout << "| ";
    print_tree(middle_part);
    cout << "| ";
    print_tree(right_part);
    cout << '\n'; */

    if (type == 1) {
      middle_part->reverse();
    } else {
      middle_part->update();
      cout << middle_part->minimum << '\n';
    }

    left_part = merge(left_part, middle_part);
    tree = merge(left_part, right_part);
    // print_tree(tree);
    // cout << '\n';
  }

  // print_tree(tree);

  return 0;
}