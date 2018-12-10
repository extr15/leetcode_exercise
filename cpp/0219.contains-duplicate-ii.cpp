class Solution {
 public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    std::map<int, vector<int>> nums_to_idx;
    for (int i = 0; i < nums.size(); i++) {
      int cur_num = nums[i];
      if (nums_to_idx.find(cur_num) != nums_to_idx.end()) {
        vector<int>& cur_indices = nums_to_idx[cur_num];
        if (i - (*cur_indices.rbegin()) <= k) {
          return true;
        }
        cur_indices.push_back(i);
      } else {
        vector<int> cur_indices;
        cur_indices.push_back(i);
        nums_to_idx.insert({cur_num, cur_indices});
      }
    }
    return false;
  }
};
