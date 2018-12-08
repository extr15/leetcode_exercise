class Solution {
 public:
  int removeElement(vector<int>& nums, int val) {
    int idx = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] != val) {
        nums[idx++] = nums[i];
      }
    }
    return idx;
  }
};

// other
int removeElement(vector<int>& nums, int val) {
  int cnt = 0;
  for (int i = 0; i < nums.size(); ++i) {
    if (nums[i] == val)
      cnt++;
    else
      nums[i - cnt] = nums[i];
  }
  return nums.size() - cnt;
}

class Solution {
 public
  void swap(int nums[], int a, int b) {
    int temp = nums[a];
    nums[a] = nums[b];
    nums[b] = temp;
  }

 public
  int removeElement(int[] nums, int val) {
    int slow = 0, count = 0;
    for (int i = 0; i < nums.length; i++) {
      if (nums[i] != val) {
        swap(nums, slow++, i);
      } else {
        count++;
      }
    }
    return nums.length - count;
  }
}
