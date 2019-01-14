#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  string addBoldTag(string s, vector<string>& dict) {
    if (s.empty()) {
      return "";
    }
    const int m = s.size();
    vector<bool> set_bold(m, false);
    for (auto& d : dict) {
      auto match_idx = kmpSearchRepeat(s, d);
      const int n = d.size();
      for (auto idx : match_idx) {
        for (int i = idx; i < idx + n; i++) {
          set_bold[i] = true;
        }
      }
    }
    string res;
    bool bold = false;
    for (int i = 0; i < m; i++) {
      if (set_bold[i]) {
        if (!bold) {
          bold = true;
          res += "<b>";
        }
        res += s[i];
      } else {
        if (bold) {
          bold = false;
          res += "</b>";
        }
        res += s[i];
      }
    }
    if (bold) {
      res += "</b>";
    }
    return res;
  }
  vector<int> kmpSearchRepeat(const string& s, const string& p) {
    vector<int> next = calcNext(p);
    const int m = s.size();
    const int n = p.size();
    int i = 0, j = 0;
    vector<int> match_idx;
    while (i < m && j < n) {
      if (j == -1 || s[i] == p[j]) {
        i++;
        j++;
        if (j == n) {
          int idx = i - j;
          match_idx.push_back(idx);
          i = idx + 1;
          j = 0;
        }
      } else {
        j = next[j];
      }
    }
    return match_idx;
  }
  vector<int> calcNext(const string& p) {
    const int n = p.size();
    vector<int> next(n, -1);
    next[0] = -1;
    int j = 0, k = -1;
    while (j < n - 1) {
      if (k == -1 || p[j] == p[k]) {
        k++;
        j++;
        if (p[j] != p[k]) {
          next[j] = k;
        } else {
          next[j] = next[k];
        }
      } else {
        k = next[k];
      }
    }
    return next;
  }
};

int main(int argc, char* argv[]) {
  string s("abcxyz123");
  vector<string> dict{"abc", "123"};
  Solution sol;
  cout << sol.addBoldTag(s, dict) << endl;
  return 0;
}
