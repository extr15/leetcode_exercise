class Solution {
 public:
  bool validWordAbbreviation(string word, string abbr) {
    const int n = word.size();
    const int m = abbr.size();
    int i = 0, j = 0;
    while (i < n && j < m) {
      int cnt = 0;
      while (j < m && (abbr[j] >= '0' && abbr[j] <= '9')) {
        if (cnt == 0 && abbr[j] == '0') {
          return false;
        }
        cnt = cnt * 10 + (abbr[j] - '0');
        j++;
      }
      if (cnt != 0) {
        i += cnt;
        continue;
      }
      if (word[i] != abbr[j]) {
        return false;
      }
      i++;
      j++;
    }
    if (i == n && j == m) {
      return true;
    }
    return false;
  }
};
