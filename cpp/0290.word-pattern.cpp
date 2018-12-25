class Solution {
 public:
  bool wordPattern(string pattern, string str) {
    unordered_map<string, string> pattern_to_string;
    const int pattern_len = pattern.size();
    int j = 0;
    for (int i = 0; i < pattern_len; i++) {
      if (j >= str.size()) {
        return false;
      }
      int start_j = j;
      while (j < str.size() && str[j] != ' ') {
        j++;
      }
      string cur_word = str.substr(start_j, j - start_j);
      string cur_pattern;
      cur_pattern += pattern[i];
      if (pattern_to_string.find(cur_pattern) == pattern_to_string.end()) {
        pattern_to_string[cur_pattern] = cur_word;
      } else if (pattern_to_string[cur_pattern] != cur_word) {
        return false;
      }
      j++;  // skip the space.
    }
    if (j < str.size()) {
      return false;
    }
    // check inverse.
    // for "abba" and "dog dog dog dog", should return false.
    unordered_map<string, int> string_to_pattern_cnt;
    for (auto ps : pattern_to_string) {
      string_to_pattern_cnt[ps.second]++;
      if (string_to_pattern_cnt[ps.second] > 1) {
        return false;
      }
    }
    return true;
  }
};
