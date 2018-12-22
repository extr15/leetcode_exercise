#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  bool isStrobogrammatic(string s) {
    const int n = s.size();
    const int half_n = n / 2;
    for (int i = 0; i <= half_n; i++) {
      if (s[i] == '6') {
        if (s[n - 1 - i] != '9') {
          return false;
        }
      } else if (s[i] == '9') {
        if (s[n - 1 - i] != '6') {
          return false;
        }
      } else if (s[i] != s[n - 1 - i]) {
        return false;
      } else if (s[i] != '8' && s[i] != '1' && s[i] != '0') {
        return false;
      }
    }
    return true;
  }
};

int main(int argc, char *argv[]) {
  Solution sol;
  cout << sol.isStrobogrammatic("88") << endl;

  return 0;
}

