#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int ALPHABET_SIZE = 26;
vector<char> ans;
int n;
int cnt;

struct Node {
  bool isTerm;
  Node* next[ALPHABET_SIZE];
  int power;

  Node() {
    isTerm = false;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
      next[i] = nullptr;
    }
  }
};

Node* root;

void add(string s) {
  Node* cur_v = root;
  for (char ch : s) {
    int c = ch - 'a';
    if (!cur_v->next[c]) {
      cur_v->next[c] = new Node();
    }
    cur_v = cur_v->next[c];
  }
  cur_v->isTerm = true;
}

void oboiti_bor_shobi_vivesti(Node* cur_v) {
  if (!cur_v) {
    return;
  } 

  if (cur_v->isTerm) {
    ans.push_back('P');
    ++cnt;
  }
  for (int c = 0; c < ALPHABET_SIZE; ++c) {
    if (cur_v->next[c]) {
      ans.push_back('a' + c);
      oboiti_bor_shobi_vivesti(cur_v->next[c]);
      if (cnt != n) {
        ans.push_back('-');
      }
    }
  }
}

int main() {
  root = new Node();
  cin >> n;
  cnt = 0;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    add(s);
  }
  oboiti_bor_shobi_vivesti(root);
  cout << ans.size() << '\n';
  for (char c : ans) {
    cout << c << '\n';
  }
  return 0;
}
