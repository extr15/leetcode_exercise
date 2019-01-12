/// Time Limit Exceeded.
class Solution {
 public:
  typedef long long SumType;
  int countRangeSum(vector<int>& nums, int lower, int upper) {
    if (nums.empty()) {
      return 0;
    }
    const int n = nums.size();
    vector<vector<SumType>> sum(n);
    vector<vector<bool>> is_calculated(n);
    for (int j = 0; j < n; j++) {
      sum[j].resize(j + 1);
      is_calculated[j].resize(j + 1, false);
    }
    int valid_cnt = 0;
    for (int j = 0; j < n; j++) {
      for (int i = 0; i <= j; i++) {
        SumType cur_sum = getOrCalcSum(nums, sum, is_calculated, j, i);
        if (cur_sum >= lower && cur_sum <= upper) {
          valid_cnt++;
        }
      }
    }
    return valid_cnt;
  }
  SumType getOrCalcSum(const vector<int>& nums, vector<vector<SumType>>& sum,
                       vector<vector<bool>>& is_calculated, int j, int i) {
    if (is_calculated[j][i]) {
      return sum[j][i];
    }
    if (j == i) {
      sum[j][i] = nums[j];
      is_calculated[j][i] = true;
    } else {
      // sum[j][i] = getOrCalcSum(nums, sum, is_calculated, j, i+1) + nums[i];
      sum[j][i] = getOrCalcSum(nums, sum, is_calculated, j - 1, i) + nums[j];
      is_calculated[j][i] = true;
    }
    return sum[j][i];
  }
};

/// will TLE.
class Solution {
 public:
  typedef long SumType;
  int countRangeSum(vector<int>& nums, int lower, int upper) {
    if (nums.empty()) {
      return 0;
    }
    const int n = nums.size();
    vector<vector<SumType>> sum(n);
    int valid_cnt = 0;
    for (int j = 0; j < n; j++) {
      sum[j].resize(j + 1);
      sum[j][j] = nums[j]; // 注意这里要对sum[j][j]判断，因为下面的[j][i]是 i < j。否则valid_cnt 会少算。或者就要在sum整个都算好后，再遍历一次去统计valid_cnt. 
      if (sum[j][j] >= lower && sum[j][j] <= upper) {
        valid_cnt++;
      }
    }
    for (int j = 1; j < n; j++) {
      for (int i = j - 1; i >= 0; i--) {
        sum[j][i] = sum[j - 1][i] + nums[j];
        if (sum[j][i] >= lower && sum[j][i] <= upper) {
          valid_cnt++;
        }
      }
    }
    return valid_cnt;
  }
};

// AC
class Solution {
 public:
  typedef long SumType;
  int countRangeSum(vector<int>& nums, int lower, int upper) {
    if (nums.empty()) {
      return 0;
    }
    const int n = nums.size();
    vector<SumType> sum(n+1, 0);
    for (int j = 0; j < n; j++) {
      sum[j+1] = sum[j] + nums[j];
    }
    return mergeSort(sum, 0, n+1, lower, upper);
  }
  int mergeSort(vector<SumType>& sum, int first, int last, int lower, int upper) {
    if (last - first <= 1) {
      return 0;
    }
    int mid = (first + last) / 2;
    int cnt = mergeSort(sum, first, mid, lower, upper) + mergeSort(sum, mid, last, lower, upper);
    int i = first, j = mid, k=mid;
    for (; i < mid; i++) {
      //int k = mid;
      while (k < last && (sum[k] - sum[i] < lower)) {
        k++;
      }
      while (j < last && (sum[j] - sum[i] <= upper)) {
        j++;
      }
      cnt += (j - k);
    }
    std::inplace_merge(sum.begin()+first, sum.begin() + mid, sum.begin() + last);
    return cnt;
  }
};
 
// Segment Tree
class Solution {
 public:
  typedef long SumType;
  struct SegmentTreeNode {
    SegmentTreeNode(SumType min_v, SumType max_v) : min_val(min_v), max_val(max_v), cnt(0), left(nullptr), right(nullptr) {};
    SumType min_val, max_val;
    int cnt;
    SegmentTreeNode* left;
    SegmentTreeNode* right;
  };
  SegmentTreeNode* buildSegmentTree(const vector<SumType>& sum, int start, int end) {
    if(start == end) {
      return nullptr;
    }
    if(start == end -1) {
      return (new SegmentTreeNode(sum[start], sum[start]));
    }
    int mid = (start+end) / 2;
    SegmentTreeNode* stn = new SegmentTreeNode(sum[start], sum[end-1]);
    stn->left = buildSegmentTree(sum, start, mid);
    stn->right = buildSegmentTree(sum, mid, end);
    return stn;
  }
  void updateSegmentTreeCnt(SegmentTreeNode* st, int val) {
    if(st == nullptr) {
      return;
    }
    if(val >= st->min_val && val <= st->max_val) {
      st->cnt++;
      updateSegmentTreeCnt(st->left, val);
      updateSegmentTreeCnt(st->right, val);
    }
  }
  int querySegmentTreeCnt(SegmentTreeNode* st, SumType lower, SumType upper) {
    if(!st) {
      return 0;
    }
    if(lower > st->max_val || upper < st->min_val) {
      return 0;
    }
    if(lower <= st->min_val && upper >= st->max_val) {
      return st->cnt;
    }
    return querySegmentTreeCnt(st->left, lower, upper) + querySegmentTreeCnt(st->right, lower, upper);
  }
  int countRangeSum(vector<int>& nums, int lower, int upper) {
    if (nums.empty()) {
      return 0;
    }
    const int n = nums.size();
    vector<SumType> sum(n+1, 0);
    for (int j = 0; j < n; j++) {
      sum[j+1] = sum[j] + nums[j];
    }
    SumType total_sum = sum[n];
    std::sort(sum.begin(), sum.end());
    auto last = std::unique(sum.begin(), sum.end());
    sum.erase(last, sum.end()); // must erase after `unique`.
    SegmentTreeNode* st = buildSegmentTree(sum, 0, sum.size());
    int cnt = 0;
    for(int i=n-1; i>=0; i--) {
      updateSegmentTreeCnt(st, total_sum);
      total_sum -= nums[i];
      cnt += querySegmentTreeCnt(st, total_sum+lower, total_sum+upper);
    }
    return cnt;
  }
};

