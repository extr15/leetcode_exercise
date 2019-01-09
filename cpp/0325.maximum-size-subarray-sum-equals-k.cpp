// TLE.
class Solution {
 public:
  int findMaxLen(vector<int>& a, int cur_idx, int start_idx, int sum) {
    const int n = a.size();
    int max_len = 0;
    if (sum == 0 && start_idx >= 0) {
      max_len = cur_idx - start_idx;
    }
    if (cur_idx == n) {
      return max_len;
    }
    if (start_idx < 0) {
      int max_2 = findMaxLen(a, cur_idx + 1, -1, sum);
      int max_1 = findMaxLen(a, cur_idx + 1, cur_idx, sum - a[cur_idx]);
      max_len = max(max_len, max_1);
      max_len = max(max_len, max_2);
    } else {
      int max_1 = findMaxLen(a, cur_idx + 1, start_idx, sum - a[cur_idx]);
      max_len = max(max_len, max_1);
    }
    return max_len;
  }
  int maxSubArrayLen(vector<int>& a, int k) { return findMaxLen(a, 0, -1, k); }
};
