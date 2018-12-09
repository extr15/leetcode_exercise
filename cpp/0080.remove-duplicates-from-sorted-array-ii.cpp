// 这种解法也可以拓展到最大允许重复k次。
class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    const int n = nums.size();
    if (n < 3) {
      return n;
    }
    int idx = 0;
    for (int i = 2; i < n; i++) {
      if (nums[idx] != nums[i]) {
        nums[idx + 2] = nums[i];
        ++idx;
      }
    }
    return (idx + 2);
  }
};

// others
// count是重复元素的个数
int removeDuplicates(vector<int>& nums) {
  int n = nums.size(), count = 0;
  for (int i = 2; i < n; i++) {
    if (nums[i] == nums[i - 2 - count]) {
      count++;
    } else {
      nums[i - count] = nums[i];
    }
  }
  return n - count;
}


