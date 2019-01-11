#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  void calcAbbr(const string& word, int idx, int last_cnt, string cur, unordered_set<string>& res) {
    const int n = word.size();
    if (idx == n) {
      if (last_cnt != 0) {
        cur += std::to_string(last_cnt);
      }
      res.insert(cur);
      return;
    }

    string next = cur;
    if (last_cnt == 0) {
      next += word[idx];
    } else {
      next += (std::to_string(last_cnt) + word[idx]);
    }
    calcAbbr(word, idx + 1, 0, next, res);
    calcAbbr(word, idx + 1, last_cnt + 1, cur, res);
  }
  int calcAbbrLen(const string& s) {
    int len = 0;
    const int n = s.size();
    for (int i = 0; i < n; i++) {
      bool is_num = false;
      while (i < n && s[i] >= '0' && s[i] <= '9') {
        is_num = true;
        i++;
      }
      if (is_num) {
        len++;
      }
      if (i < n) {
        len++;
      }
    }
    return len;
  }
  string minAbbreviation(string target, vector<string>& dictionary) {
    unordered_set<string> target_abbr;
    calcAbbr(target, 0, 0, "", target_abbr);
    unordered_set<string> dict_abbr;
    for (auto& dict : dictionary) {
      calcAbbr(dict, 0, 0, "", dict_abbr);
    }
    for (auto& d : dict_abbr) {
      target_abbr.erase(d);
    }
    int min_len = -1;
    string min_abbr;
    for (auto& s : target_abbr) {
      int len = calcAbbrLen(s);
      //cout << "s: " << s << " " << len << endl;
      if (min_len < 0 || len < min_len) {
        min_len = len;
        min_abbr = s;
      }
    }
    return min_abbr;
  }
};

class Solution {
 public:
  bool validWordAbbreviation(string word, string abbr) {
    const int n = word.size();
    const int m = abbr.size();
    int i = 0, j = 0;
    while (i < n && j < m) {
      int cnt = 0;
      while (j < m && (abbr[j] >= '0' && abbr[j] <= '9')) {
        if (cnt == 0 && abbr[j] == '0') {
          return false;
        }
        cnt = cnt * 10 + (abbr[j] - '0');
        j++;
      }
      if (cnt != 0) {
        i += cnt;
        continue;
      }
      if (word[i] != abbr[j]) {
        return false;
      }
      i++;
      j++;
    }
    if (i == n && j == m) {
      return true;
    }
    return false;
  }
  vector<string> calcAbbrWithGivenLen(string word, int ch_cnt) {
    ;
  }

  string minAbbreviation(string target, vector<string>& dictionary) {

  }
};
 
int main(int argc, char* argv[]) {
  string target("apple");
  vector<string> dict;
  //dict.push_back("blade");
  dict.push_back("");
  Solution sol;
  //cout << sol.minAbbreviation(target, dict) << endl;
  cout << sol.minAbbreviation("usaandchinaarefriends", dict) << endl;

  return 0;
}
