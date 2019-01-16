class Solution {
 public:
  double findMaxAverage(vector<int>& a, int k) {
    const int n = a.size();
    if (n < k) {
      return 0;
    }
    //int lo = 0, hi = k - 1;
    int i = 0;
    int sum = 0;
    while (i < k) {
      sum += a[i];
      i++;
    }
    int max_sum = sum;
    while (i < n) {
      sum -= a[i - k];
      sum += a[i];
      max_sum = max(max_sum, sum);
      i++;
    }
    return (double)max_sum / k;
  }
};
