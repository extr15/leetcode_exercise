class Solution {
 public:
  vector<int> countSmaller(vector<int>& nums) {
    const int n = nums.size();
    vector<int> cnts(n, 0);
    if (nums.size() <= 1) {
      return cnts;
    }
    for (int j = n - 2; j >= 0; j--) {
      int k = j + 1;
      while (k < n && nums[k] < nums[j]) {
        k++;
      }
      k--;
      cnts[j] = k - j;
      int tmp = nums[j];
      for (int i = j; i < k; i++) {
        nums[i] = nums[i + 1];
      }
      nums[k] = tmp;
    }
    return cnts;
  }
};
