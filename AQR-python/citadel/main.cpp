#include <iostream>
#include <string>
using namespace std;

string reverse(string str) {
  for (int i = 0; i <= str.size() / 2; i++) {
    std::swap(str[i], str[str.size() - 1 - i]);
  }
  return str;
}

int main() {
  cout << reverse("abcd");
}


