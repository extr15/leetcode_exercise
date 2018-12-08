class Solution {
 public:
   int removeDuplicates(vector<int>& nums) {
     const int n = nums.size();
     if( n<= 1) {
       return n;
     }
     int idx = 0;
     for(int i=1; i< n; i++) {
       if(nums[idx] != nums[i]) {
         nums[++idx] = nums[i];
       }
     }
     return (idx+1);
   }
};

// others

int removeDuplicates(int A[], int n) {
  if (n < 2) return n;
  int id = 1;
  for (int i = 1; i < n; ++i) {
    if (A[i] != A[i - 1]) {
      A[id++] = A[i];
    }
  }
  return id;
}

// count是重复元素的个数
int removeDuplicates(int A[], int n) {
  int count = 0;
  for (int i = 1; i < n; i++) {
    if (A[i] == A[i - 1]) {
      count++;
    } else {
      A[i - count] = A[i];
    }
  }
  return n - count;
}

