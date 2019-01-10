// AC.
class Solution {
 public:
  int lengthOfLongestSubstringKDistinct(string s, int k) {
    if (k <= 0) {
      return 0;
    }
    unordered_map<char, int> ch_to_idx;
    const int n = s.size();
    int start_idx = 0;
    int max_len = 0;
    for (int i = 0; i < n; i++) {
      const char& ch = s[i];
      if (ch_to_idx.size() < k || ch_to_idx.find(ch) != ch_to_idx.end()) {
        ch_to_idx[ch] = i;
        max_len = max(max_len, i - start_idx + 1);
      } else {
        char oldest_ch;
        int oldest_idx = i;
        for (auto& elem : ch_to_idx) {
          if (elem.second < oldest_idx) {
            oldest_idx = elem.second;
            oldest_ch = elem.first;
          }
        }
        start_idx = oldest_idx + 1;
        ch_to_idx.erase(oldest_ch);
        ch_to_idx.insert({ch, i});
      }
    }
    return max_len;
  }
};

// AC.
class Solution {
 public:
  int lengthOfLongestSubstringKDistinct(string s, int k) {
    if (k <= 0) {
      return 0;
    }
    unordered_map<char, int> ch_to_idx;
    map<int, char> idx_to_ch;
    const int n = s.size();
    int start_idx = 0;
    int max_len = 0;
    for (int i = 0; i < n; i++) {
      const char& ch = s[i];
      if (ch_to_idx.size() < k || ch_to_idx.find(ch) != ch_to_idx.end()) {
        ch_to_idx[ch] = i;
        max_len = max(max_len, i - start_idx + 1);
        //if (ch_to_idx.size() == k) {
          for (auto it = idx_to_ch.begin(); it != idx_to_ch.end();) {
            if (it->second == ch) {
              it = idx_to_ch.erase(it);
            } else {
              it++;
            }
          }
        //}
        idx_to_ch[i] = ch;
      } else {
        auto it = idx_to_ch.begin();
        char oldest_ch = it->second;
        int oldest_idx = it->first;
        idx_to_ch.erase(it);
        start_idx = oldest_idx + 1;
        ch_to_idx.erase(oldest_ch);
        ch_to_idx.insert({ch, i});
        idx_to_ch.insert({i, ch});
      }
    }
    return max_len;
  }
};
