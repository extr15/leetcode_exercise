class Solution {
 public:
  void sortColors(vector<int>& nums) {
    const int n = nums.size();
    int zero_cnt = 0, one_cnt = 0;
    for (int i = 0; i < n; i++) {
      if (nums[i] == 0) {
        zero_cnt++;
      } else if (nums[i] == 1) {
        one_cnt++;
      }
    }
    for (int i = 0; i < n; i++) {
      if (i < zero_cnt) {
        nums[i] = 0;
      } else if (i < zero_cnt + one_cnt) {
        nums[i] = 1;
      } else {
        nums[i] = 2;
      }
    }
  }
};

class Solution {
 public:
  void sortColors(vector<int>& nums) {
    const int n = nums.size();
    int zero_idx = 0, two_idx = n - 1;
    int i = 0;
    while (i <= two_idx) {
      if (nums[i] == 0) {
        if (i == zero_idx) {
          zero_idx++;
        } else if (i - zero_idx >= 1) {
          std::swap(nums[i], nums[zero_idx]);
          zero_idx++;
        }
        i++;
      } else if (nums[i] == 1) {
        i++;
      } else if (nums[i] == 2) {
        while (two_idx > i && nums[two_idx] == 2) {
          two_idx--;
        }
        if (two_idx == i) {
          break;
        }
        std::swap(nums[i], nums[two_idx]);
        two_idx--;
      }
    }
  }
};
