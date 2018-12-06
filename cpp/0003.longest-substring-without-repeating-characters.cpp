class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    // vector<int> char_idx(26, -1);
    map<int, int> char_idx;
    int max_sub_len = 0;
    int start = 0;
    int cur_sub_len = 0;
    for (size_t i = 0; i < s.length(); i++) {
      int ch = s[i] - 'a';
      if (char_idx.find(ch) == char_idx.end()) {
        char_idx.emplace(ch, -1);
      }
      if (char_idx[ch] < 0) {
        cur_sub_len++;
        char_idx[ch] = i;
        if (cur_sub_len > max_sub_len) {
          max_sub_len = cur_sub_len;
        }
      } else {
        for (int j = start; j < char_idx[ch]; j++) {
          int ch_tmp = s[j] - 'a';
          char_idx[ch_tmp] = -1;
          cur_sub_len--;
        }
        start = char_idx[ch] + 1;
        char_idx[ch] = i;
      }
    }
    return max_sub_len;
  }
};
