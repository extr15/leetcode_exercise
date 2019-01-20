// AC
class NumArray {
 public:
  NumArray(vector<int> nums) : num_(nums) {
    n_ = nums.size();
    long tmp = 0;
    sum_.push_back(tmp);
    for (int i = 0; i < n_; i++) {
      tmp += nums[i];
      sum_.push_back(tmp);
    }
  }

  void update(int i, int val) {
    int delta = val - num_[i];
    num_[i] = val;
    for (int j = i + 1; j < n_ + 1; j++) {
      sum_[j] += delta;
    }
  }

  int sumRange(int i, int j) { return sum_[j + 1] - sum_[i]; }

 private:
  vector<int> num_;
  vector<long> sum_;
  int n_;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

// AC. BIT.
// method 2
class NumArray {
 public:
  NumArray(vector<int> nums) : num_(nums) {
    len_ = num_.size();
    bit_.resize(len_ + 1, 0);
    for (int i = 0; i < len_; i++) {
      updateBITree(i, nums[i]);
    }
  }
  // bit[i] -- sum[0, i]
  void updateBITree(int i, int val) {
    i++;
    while (i < bit_.size()) {
      bit_[i] += val;
      i = i + (i & (-i));
    }
  }
  // sum[0, i]
  long addBITree(int i) {
    i++;
    long sum = 0;
    while (i > 0) {
      sum += bit_[i];
      i = i - (i & (-i));
    }
    return sum;
  }
  void update(int i, int val) {
    int delta = val - num_[i];
    num_[i] = val;
    updateBITree(i, delta);
  }
  int sumRange(int i, int j) { return (int)(addBITree(j) - addBITree(i - 1)); }

 private:
  int len_;
  vector<int> num_;
  vector<long> bit_;
};

// AC. BIT.
// method 3
class NumArray {
 public:
  NumArray(vector<int> nums) : num_(nums) {
    len_ = num_.size();
    bit_.resize(len_ + 1, 0);
    for (int i = 0; i < len_; i++) {
      updateBITree(i+1, nums[i]);
    }
  }
  // bit_[i] -- sum[0, i-1]
  void updateBITree(int i, int val) {
    while (i < bit_.size()) {
      bit_[i] += val;
      i = i + (i & (-i));
    }
  }
  // sum[0, i-1]
  long addBITree(int i) {
    long sum = 0;
    while (i > 0) {
      sum += bit_[i];
      i = i - (i & (-i));
    }
    return sum;
  }
  void update(int i, int val) {
    int delta = val - num_[i];
    num_[i] = val;
    updateBITree(i+1, delta);
  }
  int sumRange(int i, int j) { return (int)(addBITree(j+1) - addBITree(i)); }

 private:
  int len_;
  vector<int> num_;
  vector<long> bit_;
};

// AC
// segment tree.
class NumArray {
 public:
  struct SegmentTreeNode {
    SegmentTreeNode(long s, int lo, int hi)
        : sum(s), low_idx(lo), high_idx(hi), left(nullptr), right(nullptr){};
    SegmentTreeNode(long s, int lo, int hi, SegmentTreeNode* ln, SegmentTreeNode* rn)
        : sum(s), low_idx(lo), high_idx(hi), left(ln), right(rn){};
    long sum;
    int low_idx, high_idx;
    SegmentTreeNode *left, *right;
  };
  SegmentTreeNode* buildSegmentTree(const vector<int>& a, int lo, int hi) {
    if (lo > hi) {
      return nullptr;
    }
    if (lo == hi) {
      return (new SegmentTreeNode(a[lo], lo, hi));
    }
    int mid = (lo + hi) / 2;
    SegmentTreeNode* left = buildSegmentTree(a, lo, mid);
    SegmentTreeNode* right = buildSegmentTree(a, mid + 1, hi);
    return (new SegmentTreeNode(left->sum + right->sum, lo, hi, left, right));
  }
  void updateSegmentTree(SegmentTreeNode* st, int i, int val) {
    if (!st) {
      return;
    }
    if (i < st->low_idx || i > st->high_idx) {
      return;
    }
    st->sum += val;
    updateSegmentTree(st->left, i, val);
    updateSegmentTree(st->right, i, val);
  }
  long querySegmentTree(SegmentTreeNode* st, int i, int j) {
    //    if(!st) {
    //      return 0;
    //    }
    if (i <= st->low_idx && st->high_idx <= j) {
      return st->sum;
    }
    if (i > st->high_idx || j < st->low_idx) {
      return 0;
    }
    return querySegmentTree(st->left, i, j) + querySegmentTree(st->right, i, j);
  }
  void releaseSegmentTree(SegmentTreeNode* st) {
    if (!st) {
      return;
    }
    releaseSegmentTree(st->left);
    releaseSegmentTree(st->right);
    delete st;
  }
  NumArray(vector<int> nums) : num_(nums) { st_ = buildSegmentTree(num_, 0, num_.size() - 1); }
  void update(int i, int val) {
    int delta = val - num_[i];
    num_[i] = val;
    updateSegmentTree(st_, i, delta);
  }
  int sumRange(int i, int j) { return (int)(querySegmentTree(st_, i, j));}

 private:
  vector<int> num_;
  SegmentTreeNode* st_;
};

// AC.
// segment tree by array.
class NumArray {
 public:
  NumArray(vector<int> nums) : num_(nums) {
    const int n = num_.size();
    tree_.resize(2 * n, 0);
    for (int i = 0; i < n; i++) {
      tree_[i + n] = num_[i];
    }
    for (int i = n - 1; i > 0; i--) {
      tree_[i] = tree_[2 * i] + tree_[2 * i + 1];
    }
  }
  void updateSegmentTree(int i, int val) {
    const int n = num_.size();
    int idx = i + n;
    while (idx > 0) {
      tree_[idx] += val;
      idx = idx / 2;
    }
  }
  long sumSegmentTree(int i, int j) {
    long sum = 0;
    const int n = num_.size();
    i += n;
    j += n;
    while (i <= j) {
      if (i % 2 == 1) {
        sum += tree_[i];
        i = i / 2 + 1;
      } else {
        i = i / 2;
      }
      if (j % 2 == 1) {
        j = j / 2;
      } else {
        sum += tree_[j];
        j = j / 2 - 1;
      }
    }
    return sum;
  }
  void update(int i, int val) {
    int delta = val - num_[i];
    num_[i] = val;
    updateSegmentTree(i, delta); // Not updateSegmentTree(i, val);
  }
  int sumRange(int i, int j) { return (int)(sumSegmentTree(i, j)); }

 private:
  vector<int> num_;
  vector<long> tree_;
};

// AC.
// segment tree by array, not keep original array.
class NumArray {
 public:
  NumArray(vector<int> nums)  {
    n = nums.size();
    tree_.resize(2 * n, 0);
    for (int i = 0; i < n; i++) {
      tree_[i + n] = nums[i];
    }
    for (int i = n - 1; i > 0; i--) {
      tree_[i] = tree_[2 * i] + tree_[2 * i + 1];
    }
  }
  void updateSegmentTree(int i, int val) {
    int idx = i + n;
    tree_[idx] = val;
    idx /= 2;
    while (idx > 0) {
      tree_[idx] = tree_[idx*2] + tree_[idx*2+1];
      idx = idx / 2;
    }
  }
  long sumSegmentTree(int i, int j) {
    long sum = 0;
    i += n;
    j += n;
    while (i <= j) {
      if (i % 2 == 1) {
        // if `i` is right child.
        sum += tree_[i];
        i++;
      } 
      i /= 2;
      if (j % 2 == 0) {
        // if `j` is left child.
        sum += tree_[j];
        j--;
      }
      j /= 2;
    }
    return sum;
  }
  void update(int i, int val) {
    updateSegmentTree(i, val);
  }
  int sumRange(int i, int j) { return (int)(sumSegmentTree(i, j)); }

 private:
  int n;
  vector<long> tree_;
};
