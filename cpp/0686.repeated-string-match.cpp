#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
   // AC.
  int repeatedStringMatch(string a, string b) {
    const int m = a.size();
    const int n = b.size();
    int i = 0, j = 0;
    int repeat_cnt = 1;
    while (i < m && j < n) {
      if (a[i] == b[j]) {
        i++;
        j++;
        if (i >= m) {
          i = 0;
          repeat_cnt++;
        }
      } else {
        i = i - j + 1;
        j = 0;
        // `<=` thus can break while when `i=0`.
        while (i <= 0) {
          i += m;
        }
        repeat_cnt = 1;
      }
    }
    if (j == n) {
      // a="a", b="aa";
      if (i == 0) {
        repeat_cnt--;
      }
      return repeat_cnt;
    } else {
      return -1;
    }
  }
  // AC.
  int repeatedStringMatch(string a, string b) {
    const int m = a.size();
    const int n = b.size();
    int i = 0, j = 0;
    int repeat_cnt = 1;
    while (true) {
      if (a[i] == b[j]) {
        i++;
        j++;
        if(j==n) {
          return repeat_cnt;
        }
        if (i >= m) {
          i = 0;
          repeat_cnt++;
        }
      } else {
        i = i - j + 1;
        j = 0;
        // `<=` thus can break while when `i=0`.
        while (i <= 0) {
          i += m;
        }
        repeat_cnt = 1;
        if(i==m) {
          return -1;
        }
      }
    }
  }
};

int main(int argc, char *argv[]) {
  Solution sol;
  //string a("abaabaa"), b("abaababaab");
  string a("aabaa"), b("aaab");
  cout << sol.repeatedStringMatch(a, b) << endl;
  return 0;
}

