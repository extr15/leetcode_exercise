class Solution {
 public:
  int numWays(int n, int k) {
    if (n == 0) {
      return 0;
    }
    int last_two_same_cnt = 0, last_two_diff_cnt = k;
    for (int i = 1; i < n; i++) {
      int cur_same_cnt = last_two_diff_cnt;
      int cur_diff_cnt = last_two_same_cnt * (k - 1) + last_two_diff_cnt * (k - 1);
      last_two_same_cnt = cur_same_cnt;
      last_two_diff_cnt = cur_diff_cnt;
    }
    return last_two_same_cnt + last_two_diff_cnt;
  }
};

