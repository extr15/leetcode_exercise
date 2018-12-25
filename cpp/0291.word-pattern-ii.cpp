#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  bool check(string pattern, int p_idx, string str, int s_idx, unordered_map<string, string>& p2s,
             unordered_set<string>& word_set) {
    const int m = pattern.size();
    const int n = str.size();

    if (p_idx == m && s_idx == n) {
      return true;
    }
    if (p_idx == m || s_idx == n) {
      return false;
    }
    string cur_p = pattern.substr(p_idx, 1);
    if (p2s.find(cur_p) != p2s.end()) {
      string expect_word = p2s[cur_p];
      const int len = expect_word.length();
      if (s_idx + len > n) {
        return false;
      } else if (expect_word != str.substr(s_idx, len)) {
        return false;
      } else {
        return check(pattern, p_idx + 1, str, s_idx + len, p2s, word_set);
      }
    } else {
      for (int word_end = s_idx + 1; word_end <= n; word_end++) {
        string cur_word = str.substr(s_idx, word_end - s_idx);
        if (word_set.find(cur_word) != word_set.end()) {
          continue;
        }
        p2s.emplace(cur_p, cur_word);
        word_set.insert(cur_word);
        if (check(pattern, p_idx + 1, str, word_end, p2s, word_set)) {
          return true;
        }
        p2s.erase(cur_p);
        word_set.erase(cur_word);
      }
    }
    return false;
  }
  bool wordPatternMatch(string pattern, string str) {
    unordered_map<string, string> p2s;
    unordered_set<string> word_set;
    return check(pattern, 0, str, 0, p2s, word_set);
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  cout << sol.wordPatternMatch("d", "e") << endl;
  return 0;
}
