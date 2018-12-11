class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
      map<int, int> val_to_cnt;
      vector<int> res;
      if(nums.empty() || k==0) {
        return res;
      }
      for(int i=0;i<k;i++) {
        val_to_cnt[nums[i]]++;
      }
      res.push_back(val_to_cnt.rbegin()->first);
      for(int i=k;i<nums.size();i++) {
        if(nums[i] != nums[i-k]) {
          if(val_to_cnt[nums[i-k]]==1) {
            val_to_cnt.erase(nums[i-k]);
          }
          else {
            val_to_cnt[nums[i-k]]--;
          }
          val_to_cnt[nums[i]]++;
        }
        res.push_back(val_to_cnt.rbegin()->first);
      }
      return res;
    }
};
