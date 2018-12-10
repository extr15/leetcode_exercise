class Solution {
 public:
  bool containsDuplicate(vector<int>& nums) {
    std::set<int> nums_set;
    for (auto n : nums) {
      if (nums_set.find(n) != nums_set.end()) {
        return true;
      } else {
        nums_set.insert(n);
      }
    }
    return false;
  }
};
