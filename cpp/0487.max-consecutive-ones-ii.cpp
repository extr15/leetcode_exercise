class Solution {
 public:
  int findMaxConsecutiveOnes(vector<int>& a) {
    if (a.empty()) {
      return 0;
    }
    const int n = a.size();
    int max_len = 0;
    int prev_len = 0, cur_len = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] == 1) {
        cur_len++;
        max_len = max(max_len, prev_len + cur_len);
      } else {
        // set a[i] to `1` to handle: [1, 1, 1, 0, 0] or [0].
        max_len = max(max_len, cur_len + 1);
        if (i + 1 < n && a[i + 1] == 1) {
          // the filped `0` is `1` now, so plus one.
          prev_len = cur_len + 1;
        } else {
          prev_len = 1;
        }
        cur_len = 0;
      }
    }
    return max_len;
  }
};
