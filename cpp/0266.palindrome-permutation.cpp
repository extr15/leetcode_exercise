class Solution {
 public:
  bool canPermutePalindrome(string s) {
    unordered_map<char, int> ch_to_cnt;
    for (int i = 0; i < s.size(); i++) {
      ch_to_cnt[s[i]]++;
    }
    int odd_cnt = 0;
    for (auto c : ch_to_cnt) {
      if (c.second % 2 != 0) {
        odd_cnt++;
        if (odd_cnt > 1) {
          return false;
        }
      }
    }
    return true;
  }
};
