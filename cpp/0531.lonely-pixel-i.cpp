// AC. statistic how many `B` in each column.
class Solution {
 public:
  int findLonelyPixel(vector<vector<char>>& picture) {
    if (picture.empty() || picture[0].empty()) {
      return 0;
    }
    const int m = picture.size();
    const int n = picture[0].size();
    vector<int> row_black_cnt(m, -1);
    vector<int> col_black_cnt(n, -1);
    int longly_cnt = 0;
    for (int r = 0; r < m; r++) {
      if (row_black_cnt[r] > 0) {
        continue;
      }
      for (int c = 0; c < n; c++) {
        if (col_black_cnt[c] > 0) {
          continue;
        }
        if (picture[r][c] == 'B') {
          row_black_cnt[r] = 1;
          col_black_cnt[c] = 1;
          bool find_another = false;
          for (int i = c + 1; i < n; i++) {
            if (picture[r][i] == 'B') {
              find_another = true;
              col_black_cnt[i] = 1;
              continue;
              // break;
            }
          }
          if (find_another) {
            break;
            // continue;
          }
          for (int i = r + 1; i < m; i++) {
            if (picture[i][c] == 'B') {
              find_another = true;
              break;
            }
          }
          if (!find_another) {
            longly_cnt++;
          }
        }
      }
    }
    return longly_cnt;
  }
};

// AC.
// Let 'B'=1, 'W'=0, we sum each row and each col, if sum equal to 1, means only one `B` in that row/col.
class Solution {
 public:
  int findLonelyPixel(vector<vector<char>>& picture) {
    if (picture.empty() || picture[0].empty()) {
      return 0;
    }
    const int m = picture.size();
    const int n = picture[0].size();
    vector<int> row_val(m, 0);
    vector<int> col_val(n, 0);
    int longly_cnt = 0;
    for (int r = 0; r < m; r++) {
      for (int c = 0; c < n; c++) {
        if (picture[r][c] == 'B') {
          row_val[r]++;
          col_val[c]++;
        }
      }
    }
    int row_cnt = 0, col_cnt = 0;
    for (int i = 0; i < n; i++) {
      if (row_val[i] == 1) {
        row_cnt++;
      }
      if (col_val[i] == 1) {
        col_cnt++;
      }
    }
    return min(row_cnt, col_cnt);
  }
};
