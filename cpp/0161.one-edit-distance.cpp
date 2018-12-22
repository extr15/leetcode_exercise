class Solution {
 public:
  bool isOneEditDistance(string s, string t) {
    int m = s.size();
    int n = t.size();
    if (std::abs(m - n) > 1) {
      return false;
    }
    if (m == n) {
      int diff_cnt = 0;
      for (int i = 0; i < m; i++) {
        if (s[i] != t[i]) {
          diff_cnt++;
          if (diff_cnt > 1) {
            return false;
          }
        }
      }
      if (diff_cnt == 1) {
        return true;
      } else {
        return false;
      }
    }
    if (m > n) {
      swap(s, t);
      swap(m, n);
    }
    int i = 0, j = 0;
    int diff_cnt = 0;
    while (i < m && j < n) {
      if (s[i] != t[j]) {
        if (diff_cnt > 0) {
          return false;
        }
        j++;
        diff_cnt++;
      } else {
        i++;
        j++;
      }
    }
    return true;
  }
};
