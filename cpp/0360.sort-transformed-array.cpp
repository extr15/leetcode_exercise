class Solution {
 public:
  vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
    vector<int> res;
    if (a == 0) {
      if (b < 0) {
        std::reverse(nums.begin(), nums.end());
      }
      for (auto e : nums) {
        res.push_back(b * e + c);
      }
      return res;
    }

    double center = -(double)b / (2 * a);
    const int n = nums.size();
    if (nums[0] >= center) {
      if (a < 0) {
        std::reverse(nums.begin(), nums.end());
      }
    } else if (nums[n - 1] <= center) {
      if (a > 0) {
        std::reverse(nums.begin(), nums.end());
      }
    } else {
      vector<int> tmp;
      int left = 0, right = n - 1;
      while (left <= right) {
        if (abs(nums[left] - center) > abs(nums[right] - center)) {
          tmp.push_back(nums[left]);
          left++;
        } else {
          tmp.push_back(nums[right]);
          right--;
        }
      }
      nums = tmp;
      if (a > 0) {
        std::reverse(nums.begin(), nums.end());
      }
    }
    for (auto e : nums) {
      res.push_back(a * e * e + b * e + c);
    }
    return res;
  }
};

