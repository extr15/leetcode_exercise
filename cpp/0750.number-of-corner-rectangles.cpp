class Solution {
 public:
  int rowPairToIdx(int r1, int r2, int m) { return (r1 * m + r2); }
  pair<int, int> idxToRowPair(int idx, int m) { return make_pair(idx / m, idx % m); }
  int countCornerRectangles(vector<vector<int>>& grid) {
    const int m = grid.size();
    const int n = grid[0].size();
    if (m == 1 || n == 1) {
      return 0;
    }
    unordered_map<int, int> row_pair_idx_to_cnt;
    int rect_cnt = 0;
    for (int j = 0; j < n; j++) {
      for (int i1 = 0; i1 < m - 1; i1++) {
        if (grid[i1][j] == 0) {
          continue;
        }
        for (int i2 = i1 + 1; i2 < m; i2++) {
          if (grid[i2][j] == 0) {
            continue;
          }
          int idx = rowPairToIdx(i1, i2, m);
          rect_cnt += row_pair_idx_to_cnt[idx];
          row_pair_idx_to_cnt[idx]++;
        }
      }
    }
    return rect_cnt;
  }
};
