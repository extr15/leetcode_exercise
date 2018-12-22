#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Wrong Answer, Not finish.
class Solution2 {
 public:
  void helper(char* ch, int left, int right, vector<string>& res, int len, const string& lower,
              const string& upper) {
    if (left > right) {
      res.push_back(string(ch));
      return;
    }
    bool valid0 = true, valid1 = true, valid8 = true, valid6 = true, valid9 = true;
    if (len == lower.size()) {
      if (lower[left] > '8' || (lower[left] == '8' && lower[len - 1 - left] > '8')) {
        valid8 = false;
      }
      if (lower[left] > '1' || (lower[left] == '1' && lower[len - 1 - left] > '1')) {
        valid1 = false;
      }
      if (lower[left] > '6' || (lower[left] == '6' && lower[len - 1 - left] > '9')) {
        valid6 = false;
      }
      if (lower[left] > '9' || (lower[left] == '9' && lower[len - 1 - left] > '6')) {
        valid9 = false;
      }
      if (lower[left] > '0' || (lower[left] == '0' && lower[len - 1 - left] > '0')) {
        valid0 = false;
      }
    }
    if (len == upper.size()) {
      if (upper[left] < '8' || (upper[left] == '8' && upper[len - 1 - left] < '8')) {
        valid8 = false;
      }
      if (upper[left] < '1' || (upper[left] == '1' && upper[len - 1 - left] < '1')) {
        valid1 = false;
      }
      if (upper[left] < '6' || (upper[left] == '6' && upper[len - 1 - left] < '9')) {
        valid6 = false;
      }
      if (upper[left] < '9' || (upper[left] == '9' && upper[len - 1 - left] < '6')) {
        valid9 = false;
      }
    }
    if (left == right) {
      if (valid0) {
        ch[left] = '0';
        res.push_back(string(ch));
      }
      if (valid1) {
        ch[left] = '1';
        res.push_back(string(ch));
      }
      if (valid8) {
        ch[left] = '8';
        res.push_back(string(ch));
      }
      return;
    }
    if (valid0 && left != 0) {
      ch[left] = ch[right] = '0';
      helper(ch, left + 1, right - 1, res, len, lower, upper);
    }
    if (valid1) {
      ch[left] = ch[right] = '1';
      helper(ch, left + 1, right - 1, res, len, lower, upper);
    }
    if (valid8) {
      ch[left] = ch[right] = '8';
      helper(ch, left + 1, right - 1, res, len, lower, upper);
    }
    if (valid6) {
      ch[left] = '6';
      ch[right] = '9';
      helper(ch, left + 1, right - 1, res, len, lower, upper);
    }
    if (valid9) {
      ch[left] = '9';
      ch[right] = '6';
      helper(ch, left + 1, right - 1, res, len, lower, upper);
    }
  }
  int strobogrammaticInRange(string low, string high) {
    const int m = low.size();
    const int n = high.size();
    char* ch = new char[n + 1];
    ch[n] = '\0';
    vector<string> res;
    for (int k = m; k <= n; k++) {
      helper(ch, 0, k - 1, res, k, low, high);
    }
    cout << "res: " << endl;
    for (auto s : res) {
      cout << s << endl;
    }
    return res.size();
  }
};

// AC.
class Solution {
 public:
  bool checkInRange(const string& str, const string& lower, const string& upper) {
    if (str.size() == lower.size()) {
      for (int i = 0; i < str.size(); i++) {
        if (lower[i] < str[i]) {
          break;
        } else if (lower[i] > str[i]) {
          return false;
        }
      }
    }
    if (str.size() == upper.size()) {
      for (int i = 0; i < str.size(); i++) {
        if (upper[i] > str[i]) {
          break;
        } else if (upper[i] < str[i]) {
          return false;
        }
      }
    }
    return true;
  }
  void helper(char* ch, int left, int right, vector<string>& res, const string& lower,
              const string& upper) {
    if (left > right) {
      string str = string(ch);
      if (checkInRange(str, lower, upper)) {
        res.push_back(str);
      }
      return;
    }
    if (left == right) {
      ch[left] = '0';
      string str = string(ch);
      if (checkInRange(str, lower, upper)) {
        res.push_back(str);
      }
      ch[left] = '1';
      str = string(ch);
      if (checkInRange(str, lower, upper)) {
        res.push_back(str);
      }
      ch[left] = '8';
      str = string(ch);
      if (checkInRange(str, lower, upper)) {
        res.push_back(str);
      }
      return;
    }
    if (left != 0) {
      ch[left] = ch[right] = '0';
      helper(ch, left + 1, right - 1, res, lower, upper);
    }
    ch[left] = ch[right] = '1';
    helper(ch, left + 1, right - 1, res, lower, upper);
    ch[left] = ch[right] = '8';
    helper(ch, left + 1, right - 1, res, lower, upper);
    ch[left] = '6';
    ch[right] = '9';
    helper(ch, left + 1, right - 1, res, lower, upper);
    ch[left] = '9';
    ch[right] = '6';
    helper(ch, left + 1, right - 1, res, lower, upper);
  }
  int strobogrammaticInRange(string low, string high) {
    const int m = low.size();
    const int n = high.size();
    char* ch = new char[n + 1];
    ch[n] = '\0';
    vector<string> res;
    for (int k = m; k <= n; k++) {
      ch[k] = '\0';
      helper(ch, 0, k - 1, res, low, high);
    }
    return res.size();
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  //int cnt = sol.strobogrammaticInRange("0", "1680");
  int cnt = sol.strobogrammaticInRange("0", "2147483647");
  cout << "cnt: " << cnt << endl;
  return 0;
}

