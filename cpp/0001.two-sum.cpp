class Solution {
 public:
   /*
    template <typename T>
    static std::vector<size_t> calcSortIndexes(const std::vector<T> &v) {
      // initialize original index locations
      std::vector<size_t> idx(v.size());
      std::iota(idx.begin(), idx.end(), 0);

      // sort indexes based on comparing values in v
      std::sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) { return v[i1] < v[i2]; });

      return idx;
    }
    */
  void sortByIndex(const vector<int>& nums, vector<int>* sort_idx) {
    std::vector<int> idx(nums.size());
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(),
              [&](int a, int b) { return nums[a] < nums[b]; });
    *sort_idx = idx;
  }

  vector<int> twoSum(vector<int>& nums, int target) {
    std::vector<int> res;
    if (nums.size() <= 1) {
      return res;
    }
    std::vector<int> sort_idx;
    sortByIndex(nums, &sort_idx);
    // std::sort(nums.begin(), nums.end());
    for (size_t si = 0, sj = sort_idx.size() - 1;
         (si < sort_idx.size()) && (sj > si);) {
      int i = sort_idx[si];
      int j = sort_idx[sj];
      int sum = nums[i] + nums[j];
      if (sum > target) {
        sj--;
      } else if (sum < target) {
        si++;
      } else {
        res.push_back(i);
        res.push_back(j);
        break;
      }
    }
    return res;
  }
};

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    std::vector<int> res;
    if (nums.size() <= 1) {
      return res;
    }

    std::map<int, std::vector<int>> val_to_idx;
    for (size_t i = 0; i < nums.size(); i++) {
      const int n = nums[i];
      if (val_to_idx.find(n) == val_to_idx.end()) {
        std::vector<int> idx;
        idx.push_back(i);
        val_to_idx.emplace(n, idx);
      } else {
        val_to_idx[n].push_back(i);
      }
    }
    for (auto& m : val_to_idx) {
      int d = target - m.first;
      if (d == m.first) {
        auto& idx = m.second;
        if (idx.size() > 1) {
          res.push_back(idx[0]);
          res.push_back(idx[1]);
          break;
        }
      } else if (val_to_idx.find(d) != val_to_idx.end()) {
        auto& idx1 = m.second;
        auto& idx2 = val_to_idx[d];
        res.push_back(idx1[0]);
        res.push_back(idx2[0]);
        break;
      }
    }
    return res;
  }
};
