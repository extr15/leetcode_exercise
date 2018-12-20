class Solution {
 public:
  int lengthOfLongestSubstringTwoDistinct(string s) {
    if (s.size() <= 2) {
      return s.size();
    }
    unordered_map<char, int> ch_to_idx;
    int idx1, idx2 = -1;
    char last_ch1, last_ch2;
    int start_idx = 0;
    int max_len = 0;
    for (int i = 0; i < s.size(); i++) {
      const char ch = s[i];
      if (ch_to_idx.find(ch) == ch_to_idx.end()) {
        if (ch_to_idx.size() == 2) {
          ch_to_idx.erase(last_ch2);
        }
        ch_to_idx.insert({ch, i});
        start_idx = idx2 + 1;
        if(ch_to_idx.size() > 1) {
          idx2 = idx1;
          last_ch2 = last_ch1;
        }
        idx1 = i;
        last_ch1 = ch;
      } else {
        if (idx2 >=0 && ch == last_ch2) {
          last_ch2 = last_ch1;
          idx2 = idx1;
        }
        last_ch1 = ch;
        idx1 = i;
      }
      max_len = max(max_len, i - start_idx + 1);
    }
    return max_len;
  }
};


class Solution {
 public:
  int lengthOfLongestSubstringTwoDistinct(string s) {
    if (s.size() <= 2) {
      return s.size();
    }
    int start_idx=0, idx1=0, idx2 = -1;
    int max_len = 0;
    for(int i=1;i<s.size();i++) {
      if(s[i] == s[idx1]) {
        idx1 = i;
      }
      else if(idx2>=0 && s[i] == s[idx2]) {
        idx2 = idx1;
        idx1 = i;
      }
      else {
        start_idx = idx2+1;
        idx2 = idx1;
        idx1 = i;
      };
      max_len = max(max_len, i - start_idx + 1);
    }
    return max_len;
  }
};


