// AC
class Solution {
 public:
  void rotate(vector<int>& nums, int k) {
    const int n = nums.size();
    if (n == 0 || (k % n == 0)) {
      return;
    }
    k = k % n;
    vector<int> tmp;
    std::copy(nums.begin(), nums.begin() + (n - k), std::back_inserter(tmp));
    for (int i = 0; i < k; i++) {
      nums[i] = nums[i + (n - k)];
    }
    std::copy(tmp.begin(), tmp.end(), nums.begin() + k);
  }
};

// not finish
class Solution {
 public:
  void rotate(vector<int>& nums, int k) {
    const int n = nums.size();
    if (n == 0 || (k % n == 0)) {
      return;
    }
    k = k % n;
    if(n%k == 0) {
      //int c = n / k;
      for(int j=0; j < k; j++) {
        int p = n - j;
        int t = nums[j];
        for(; p < n-k; p+=k) {
          nums[j] = nums[p+k];
        }
        nums[p+k] = t;
      }
    }
    else {
      .
    }
  }
};

