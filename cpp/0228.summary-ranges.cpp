class Solution {
 public:
  vector<string> summaryRanges(vector<int>& nums) {
    const int n = nums.size();
    vector<string> res;
    if (n == 0) {
      return res;
    }
    string cur_str;
    const string arrow = "->";
    cur_str = std::to_string(nums[0]);
    bool have_next = false;
    for (int i = 0; i < n - 1; i++) {
      if (nums[i] + 1 == nums[i + 1]) {
        have_next = true;
        continue;
      } else {
        if (have_next) {
          cur_str += (arrow + std::to_string(nums[i]));
        }
        res.push_back(cur_str);
        cur_str = std::to_string(nums[i + 1]);
        have_next = false;
      }
    }
    if (have_next) {
      cur_str += (arrow + std::to_string(nums[n - 1]));
    }
    res.push_back(cur_str);
    return res;
  }
};
