class Solution {
 public:
  int maximumGap(vector<int>& nums) {
    if (nums.size() < 2) {
      return 0;
    }
    std::sort(nums.begin(), nums.end());
    int max_gap = std::numeric_limits<int>::min();
    for (int i = 0; i < nums.size() - 1; i++) {
      int gap = nums[i + 1] - nums[i];
      max_gap = (gap > max_gap) ? gap : max_gap;
    }
    return max_gap;
  }
};
