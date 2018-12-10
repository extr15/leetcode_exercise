class Solution {
 public:
  bool canJump(vector<int>& nums) {
    const int n = nums.size();
    int i = 0;
    int max_i = 0;
    while (i <= max_i) {
      int jump_i = nums[i] + i;
      if (jump_i > max_i) {
        max_i = jump_i;
        if (max_i >= n - 1) {
          return true;
        }
      }
      i++;
    }
    return (max_i >= n -1);
  }
};
