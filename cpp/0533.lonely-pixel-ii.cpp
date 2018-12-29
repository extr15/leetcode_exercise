class Solution {
 public:
  int findBlackPixel(vector<vector<char>>& picture, int N) {
    if (picture.empty() || picture[0].empty()) {
      return 0;
    }
    //unordered_map<vector<int>, int> black_col_idx_to_cnt;
    map<vector<int>, int> black_col_idx_to_cnt;
    const int rows = picture.size();
    const int cols = picture[0].size();
    vector<int> black_cnt_per_col(cols, 0);
    for (int r = 0; r < rows; r++) {
      int black_cnt = 0;
      vector<int> black_col_idx;
      for (int c = 0; c < cols; c++) {
        if (picture[r][c] == 'B') {
          black_cnt++;
          black_cnt_per_col[c]++;
          black_col_idx.push_back(c);
        }
      }
      if (black_cnt == N) {
        black_col_idx_to_cnt[black_col_idx]++;
      }
    }
    int total_black_cnt = 0;
    for(auto col_idx : black_col_idx_to_cnt) {
      if(col_idx.second == N) {
        for(auto col : col_idx.first) {
          if(black_cnt_per_col[col] == N) {
            total_black_cnt += N;
          }
        }
      }
    }
    return total_black_cnt;
  }
};
