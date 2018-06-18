#include <bits/stdc++.h>

//ZOHODI POJAJA

int main() {
  std::regex re1("\\{(.|\\n)*\\}");
  std::regex re2("/\\*(.|\\n)*\\*/");
  std::regex re3("//.*\n");

  std::string text;
  std::string buffer;

  while (std::getline(std::cin, buffer)) {
    text += buffer + '\n';
  }
  
  text =  std::regex_replace(std::regex_replace(std::regex_replace(text, re1, ""), re2, ""), re3, "");
  text.pop_back();

  std::cout << text;

  return 0;
}