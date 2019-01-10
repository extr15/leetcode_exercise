#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// TLE.
class Solution {
 public:
  void findWordSquare(vector<unordered_map<string, bool>>& each_row_available_str, int row,
                      int word_len, vector<string>& word_seq, vector<vector<string>>& res) {
    if (row == word_len) {
      res.push_back(word_seq);
      return;
    }
    auto& available_str = each_row_available_str[row];

    for (auto& s : available_str) {
      if (!s.second) {
        continue;
      }
      vector<unordered_set<string>> disable_str(word_len - row - 1);
      bool one_empty_row = false;
      for (int i = row + 1; i < word_len; i++) {
        auto& next_str = each_row_available_str[i];
        int available_cnt = 0;
        for (auto& s2 : next_str) {
          if (s2.second == false) {
            continue;
          }
          if (s.first[i] != s2.first[row]) {
            disable_str[i - row - 1].insert(s2.first);
          } else {
            available_cnt++;
          }
        }
        if (available_cnt == 0) {
          one_empty_row = true;
          break;
        }
      }
      if (one_empty_row) {
        continue;
      }

      for (int i = 0; i < disable_str.size(); i++) {
        for (auto& s2 : disable_str[i]) {
          each_row_available_str[i + row + 1][s2] = false;
        }
      }
      word_seq.push_back(s.first);
      findWordSquare(each_row_available_str, row + 1, word_len, word_seq, res);
      word_seq.pop_back();
      for (int i = 0; i < disable_str.size(); i++) {
        for (auto& s2 : disable_str[i]) {
          each_row_available_str[i + row + 1][s2] = true;
        }
      }
    }
  }
  vector<vector<string>> wordSquares(vector<string>& words) {
    const int n = words.size();
    const int word_len = words[0].length();
    vector<unordered_map<string, bool>> each_row_available_str(word_len);
    unordered_set<string> word_set;
    for (auto s : words) {
      for (int i = 0; i < word_len; i++) {
        each_row_available_str[i].emplace(s, true);
      }
    }

    vector<vector<string>> res;
    vector<string> word_seq;
    findWordSquare(each_row_available_str, 0, word_len, word_seq, res);
    return res;
  }
};

class Solution2 {
 public:
  vector<vector<string>> wordSquares(vector<string>& words) {
    n = words[0].size();
    square.resize(n);
    for (string word : words)
      for (int i = 0; i < n; i++) fulls[word.substr(0, i)].push_back(word);
    build(0);
    return squares;
  }
  int n;
  unordered_map<string, vector<string>> fulls;
  vector<string> square;
  vector<vector<string>> squares;
  void build(int i) {
    if (i == n) {
      squares.push_back(square);
      return;
    }
    string prefix;
    for (int k = 0; k < i; k++) prefix += square[k][i];
    for (string word : fulls[prefix]) {
      square[i] = word;
      build(i + 1);
    }
  }
};

int main(int argc, char* argv[]) {
  Solution2 sol;
  vector<string> words;
  words.push_back("wall");
  words.push_back("area");
  words.push_back("lady");
  words.push_back("lead");

  auto res = sol.wordSquares(words);
  for (auto& sq : res) {
    cout << "------- square: " << endl;
    for (auto& s : sq) {
      cout << s << endl;
    }
    cout << endl;
  }

  return 0;
}
