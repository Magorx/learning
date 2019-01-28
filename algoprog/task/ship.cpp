#include <bits/stdc++.h>
#include <string>

using namespace std;

const long long inf = 1e10;

long long randint() {
  return (rand() << 16) ^ rand();
}

template <typename T>
struct Node;

template <typename T>
long long node_min(Node<T>* n);

template <typename T>
long long node_size(Node<T>* n);

template <typename T>
struct Node {
  T val;
  long long pr;
  Node *l;
  Node *r;
  int size;

  T min_val;

  Node() {}
  Node(T value, int priority) {
    val = value;
    pr = priority;
    size = 1;
    l = nullptr;
    r = nullptr;
  }
  Node(T value) {
    val = value;
    pr = randint();
    min_val = value;
    size = 1;
    l = nullptr;
    r = nullptr;
  }

  void update() {
    min_val = min(min(val, node_min(l)), node_min(r));
    size = node_size(l) + node_size(r) + 1;
  }
};

template <typename T>
long long node_min(Node<T>* n) {
  if (!n) {
    return +inf;
  } else {
    return n->min_val;
  }
}

template <typename T>
long long node_size(Node<T>* n) {
  if (!n) {
    return 0;
  } else {
    return n->size;
  }
}

template <typename T>
pair<Node<T>*, Node<T>*> split(Node<T>* n, T key) {
  if (!n) {
    return {nullptr, nullptr};
  }

  pair<Node<T>*, Node<T>*> ret;
  if (n->val <= key) {
    ret = split(n->r, key);
    n->r = ret.first;
    n->update();
    return {n, ret.second};
  } else {
    ret = split(n->l, key);
    n->l = ret.second;
    n->update();
    return {ret.first, n};
  }
}

template <typename T>
Node<T>* merge(Node<T>* l, Node<T>* r) {
  if (!l) {
    return r;
  } else if (!r) {
    return l;
  }

  if (l->pr > r->pr) {
    l->r = merge(l->r, r);
    l->update();
    return l;
  } else {
    r->l = merge(l, r->l);
    r->update();
    return r;
  }
}

template <typename T>
Node<T>* insert(Node<T>* n, Node<T>* new_node) {
  if (!n) {
    return new_node;
  }

  if (new_node->pr > n->pr) {
    tie(new_node->l, new_node->r) = split(n, new_node->val);
    new_node->update();
    return new_node;
  } else {
    if (new_node->val > n->val) {
      n->r = insert(n->r, new_node);
    } else {
      n->l = insert(n->l, new_node);
    }
    n->update();
    return n;
  }
}

template <typename T>
Node<T>* del(Node<T>* t, T value) {
  Node<T>* ret1;
  Node<T>* ret2;
  Node<T>* ret3;
  tie(ret1, ret2) = split(t, value);
  tie(ret1, ret3) = split(ret1, value - 1);
  Node<T>* merged = merge(ret1, ret2);
  return merged;
}

template <typename T>
Node<T>* find(Node<T> *n, T val) {
  if (!n) {
    return nullptr;
  }
  if (n->val == val) {
    return n;
  }

  if (n->val > val) {
    Node<T> *ret = find(n->l, val);
    if (ret) {
      return ret;
    } else {
      return n;
    }
  } else {
    Node<T> *ret = find(n->l, val);
    if (ret) {
      return ret;
    } else {
      return nullptr;
    }
  }
}

template <typename T>
Node<T>* indexed(Node<T> *n, int index) {
  if (!n) {
    return nullptr;
  }

  if (node_size(n->l) == index) {
    return n;
  } else if (node_size(n->l) < index) {
    return indexed(n->r, index - node_size(n->l) - 1);
  } else {
    return indexed(n->l, index);
  }
}

template<typename T>
void print_tree(Node<T>* n) {
  if (!n) {
  return;
  }

  print_tree(n->l);
  cout << n->val << ' ';
  print_tree(n->r);
}


int main() {
  Node<long long> *tree = nullptr;
  int n = 0;
  cin >> n;

  while (n--) {
    int type;
    long long value;
    cin >> type >> value;
    if (type == 1) {
      tree = insert(tree, new Node<long long>(value));

      int l = -1;
      int r = tree->size - 1;
      Node<long long> *ret;
      while (r - l > 1) {
        int m = (l + r) / 2;
        //cout << l << ' ' << r << ' ' << m << '\n';
        ret = indexed(tree, m);
        if (ret->val >= value) {
          r = m;
        } else {
          l = m;
        }
      }
      cout << tree->size - (l + 2) << '\n';
    } else {
      tree = del(tree, indexed(tree, value)->val);
    }
  }
  return 0;
}