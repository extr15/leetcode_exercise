class Solution {
 public:
  int pathSum(vector<int>& a) {
    if (a.empty()) {
      return 0;
    }
    vector<int> tree(16, -1);
    int max_depth = -1;
    for (auto v : a) {
      int depth = v / 100;
      int level = (v - depth * 100) / 10;
      int val = v % 10;
      int idx = pow(2, depth - 1) + (level - 1);
      tree[idx] = val;
      max_depth = max(max_depth, depth);
    }
    int sum = 0;
    vector<bool> is_leaf(16, true);
    for (int d = max_depth; d >= 1; d--) {
      for (int i = pow(2, d - 1); i < pow(2, d); i++) {
        if (tree[i] < 0 || !is_leaf[i]) {
          continue;
        }
        int k = i;
        while (k > 0) {
          sum += tree[k];
          k /= 2;
          is_leaf[k] = false;
        }
      }
    }
    return sum;
  }
};
