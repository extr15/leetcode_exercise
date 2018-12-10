// TLE
class Solution {
 public:
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    const int n = nums.size();
    if (t < 0 || k < 1) {
      return false;
    }
    const long long_t = (long)t;
    for (int i = 0; i < n; i++) {
      const long cur_num = nums[i];
      for (int j = i + 1; j < std::min(i + k + 1, n); j++) {
        const long cur_num_j = nums[j];
        if (std::abs(cur_num - cur_num_j) <= long_t) {
          return true;
        }
      }
    }
    return false;
  }
};

// AC
class Solution {
 public:
  int calcBucketId(int a, int bucket_len) {
    if (a > 0) {
      return a / bucket_len;
    } else {
      return (a / bucket_len) - 1;
    }
  }
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    const int n = nums.size();
    if (t < 0 || k < 1) {
      return false;
    }
    map<int, int> bucket_to_nums_idx;
    const long long_t = (long)t;
    for (int i = 0; i < n; i++) {
      const int cur_num = nums[i];
      int cur_bucket_id = calcBucketId(cur_num, t + 1);
      if (bucket_to_nums_idx.find(cur_bucket_id) != bucket_to_nums_idx.end()) {
        return true;
      }
      if (bucket_to_nums_idx.find(cur_bucket_id - 1) != bucket_to_nums_idx.end()) {
        const long prev_num = (long)(nums[bucket_to_nums_idx[cur_bucket_id - 1]]);
        if (std::abs((long)cur_num - prev_num) <= long_t) {
          return true;
        }
      }
      if (bucket_to_nums_idx.find(cur_bucket_id + 1) != bucket_to_nums_idx.end()) {
        const long prev_num = (long)nums[bucket_to_nums_idx[cur_bucket_id + 1]];
        if (std::abs((long)cur_num - prev_num) <= long_t) {
          return true;
        }
      }
      bucket_to_nums_idx.insert({cur_bucket_id, i});
      if (i >= k) {
        bucket_to_nums_idx.erase(calcBucketId(nums[i - k], t + 1));
      }
    }
    return false;
  }
};
