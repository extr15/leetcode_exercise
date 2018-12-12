class Solution {
 public:
  int strStr(string haystack, string needle) {
    if (needle.empty()) {
      return 0;
    }
    if (haystack.empty()) {
      return -1;
    }
    const int len = haystack.length();
    const int needle_len = needle.length();
    for (int i = 0; i <= len - needle_len; i++) {
      bool same_word = true;
      for (int j = 0; j < needle_len; j++) {
        if (needle[j] != haystack[i + j]) {
          same_word = false;
          break;
        }
      }
      if (same_word) {
        return i;
      }
    }
    return -1;
  }
};
