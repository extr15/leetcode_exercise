class Solution {
 public:
  void generatePalindromes(unordered_map<char, int>& ch_to_cnt, string& s, int left, int right,
                           vector<string>& res) {
    if (left > right) {
      res.push_back(s);
      return;
    }
    if (left == right) {
      for (auto c : ch_to_cnt) {
        if (c.second == 1) {
          s[left] = c.first;
          res.push_back(s);
          return;
        }
      }
    }
    for (auto& c : ch_to_cnt) {
      if (c.second >= 2) {
        s[left] = s[right] = c.first;
        c.second -= 2;
        generatePalindromes(ch_to_cnt, s, left + 1, right - 1, res);
        c.second += 2;
      }
    }
  }
  vector<string> generatePalindromes(string s) {
    vector<string> res;
    unordered_map<char, int> ch_to_cnt;
    const int n = s.size();
    if (n == 0) {
      res.push_back(s);
      return res;
    }
    for (int i = 0; i < s.size(); i++) {
      ch_to_cnt[s[i]]++;
    }
    int odd_cnt = 0;
    for (auto c : ch_to_cnt) {
      if (c.second % 2 != 0) {
        odd_cnt++;
        if (odd_cnt > 1) {
          return res;
        }
      }
    }
    generatePalindromes(ch_to_cnt, s, 0, n - 1, res);
    return res;
  }
};
