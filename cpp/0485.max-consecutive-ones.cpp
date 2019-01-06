class Solution {
 public:
  int findMaxConsecutiveOnes(vector<int>& a) {
    const int n = a.size();
    int max_cnt = 0;
    int start = -1;
    for (int i = 0; i < n; i++) {
      if (a[i] == 1) {
        max_cnt = max(max_cnt, i - start);
      } else {
        start = i;
      }
    }
    return max_cnt;
  }
};
