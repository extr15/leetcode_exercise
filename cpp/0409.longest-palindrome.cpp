class Solution {
 public:
  int longestPalindrome(string s) {
    map<int, int> ch_to_cnt;
    for (auto ch : s) {
      int idx = (ch - 'a');
      ch_to_cnt[ch]++;
    }
    bool has_odd = false;
    int pair_cnt = 0;
    for (auto& e : ch_to_cnt) {
      int cnt = e.second;
      if (cnt % 2 == 1) {
        has_odd = true;
        cnt--;
      }
      pair_cnt += cnt;
    }
    if (has_odd) {
      pair_cnt++;
    }
    return pair_cnt;
  }
};
