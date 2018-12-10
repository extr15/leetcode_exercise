class Solution {
 public:
  int jump(vector<int>& nums) {
    const int n = nums.size();
    vector<int> father_idx(n);
    int i = 0;
    int max_i = 0;
    father_idx[0] = 0;
    int last_i = 0;
    while (i <= max_i) {
      int cur_i = nums[i] + i;
      if (cur_i > max_i) {
        max_i = cur_i;
        if (max_i >= n - 1) {
          father_idx[n - 1] = i;
          break;
        }
        for (int j = last_i + 1; j <= max_i; j++) {
          father_idx[j] = i;
        }
        last_i = max_i;
      }
      i++;
    }
    int jump_cnt = 0;
    if (max_i >= n - 1) {
      int back_i = n - 1;
      while (back_i > 0) {
        back_i = father_idx[back_i];
        jump_cnt++;
      }
      return jump_cnt;
    } else {
      return -1;
    }
  }
};
