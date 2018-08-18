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
    cur_v->power += 1;
    if (!cur_v->next[c]) {
      cur_v->next[c] = new Node();
    }
    cur_v = cur_v->next[c];
  }
  cur_v->isTerm = true;
}

string get_k_str(Node* cur_v, int k) {
  int cur_k = 0;
  for (int i = 0; i < ALPHABET_SIZE; ++i) {
    if (cur_v->next[i]) {
      cur_k += cur_v->next[i]->power;
      if (cur_k >= k) {
        cur_k -= cur_v->next[i]->power;
        get_k_str(cur_v->next[i], k - cur_k);
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
  cout << ans.size() << '\n';
  for (char c : ans) {
    cout << c << '\n';
  }
  return 0;
}
