class Solution {
 public:
  int subarraySum(vector<int>& a, int k) {
    const int n = a.size();
    // vector<int> sum(n+1);
    int cur_sum = 0;
    unordered_map<int, int> sum_to_cnt;
    sum_to_cnt.insert({0, 1});
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      cur_sum += a[i];
      int prev_sum = cur_sum - k;
      if (sum_to_cnt.find(prev_sum) != sum_to_cnt.end()) {
        cnt += sum_to_cnt[prev_sum];
      }
      sum_to_cnt[cur_sum]++;
    }
    return cnt;
  }
};
