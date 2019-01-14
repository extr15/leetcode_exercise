// AC. brute force.
class Solution {
 public:
  int longestLine(vector<vector<int>>& a) {
    if (a.empty() || a[0].empty()) {
      return 0;
    }
    const int m = a.size();
    const int n = a[0].size();
    vector<int> col_max_cnt(n);
    vector<int> diag_max_cnt(m + n - 1);
    vector<int> anti_diag_max_cnt(m + n - 1);
    int res = 0;
    for (int i = 0; i < m; i++) {
      int row_cnt = 0;
      for (int j = 0; j < n; j++) {
        if (a[i][j] == 0) {
          row_cnt = 0;
          continue;
        }
        row_cnt++;
        res = max(res, row_cnt);
        if (col_max_cnt[j] == 0) {
          int cnt = 1;
          int max_cnt = 1;
          for (int k = i + 1; k < m; k++) {
            if (a[k][j] == 1) {
              cnt++;
              max_cnt = max(max_cnt, cnt);
            } else {
              cnt = 0;
            }
          }
          res = max(res, max_cnt);
          col_max_cnt[j] = max_cnt;
        }
        const int diag = j - i + (m - 1);
        if (diag_max_cnt[diag] == 0) {
          int cnt = 1;
          int max_cnt = 1;
          for (int k = i + 1, s = j + 1; k < m && s < n; k++, s++) {
            if (a[k][s] == 1) {
              cnt++;
              max_cnt = max(max_cnt, cnt);
            } else {
              cnt = 0;
            }
          }
          res = max(res, max_cnt);
          diag_max_cnt[diag] = max_cnt;
        }
        const int anti_diag = i + j;
        if (anti_diag_max_cnt[anti_diag] == 0) {
          int cnt = 1;
          int max_cnt = 1;
          for (int k = i + 1, s = j - 1; k < m && s >= 0; k++, s--) {
            if (a[k][s] == 1) {
              cnt++;
              max_cnt = max(max_cnt, cnt);
            } else {
              cnt = 0;
            }
          }
          res = max(res, max_cnt);
          anti_diag_max_cnt[anti_diag] = max_cnt;
        }
      }
    }
    return res;
  }
};

// Wrong. dp.
// should store diag(dp[j][2]) to be used in next column.
// [[0,1,1,0],[0,1,1,0],[0,0,0,1]]
class Solution {
 public:
  int longestLine(vector<vector<int>>& a) {
    if (a.empty() || a[0].empty()) {
      return 0;
    }
    const int m = a.size();
    const int n = a[0].size();
    vector<vector<int>> dp(n, vector<int>(4, 0));
    int res = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (a[i][j] == 1) {
          dp[j][0] = j > 0 ? dp[j - 1][0] + 1 : 1;
          dp[j][1]++;
          dp[j][2] = j > 0 ? dp[j - 1][2] + 1 : 1;
          dp[j][3] = j < n - 1 ? dp[j + 1][3] + 1 : 1;
          for (int k = 0; k < 4; k++) {
            res = max(res, dp[j][k]);
          }
        } else {
          dp[j][0] = dp[j][1] = dp[j][2] = dp[j][3] = 0;
        }
      }
    }
    return res;
  }
};

// AC. dp. v1
class Solution {
 public:
  int longestLine(vector<vector<int>>& a) {
    if (a.empty() || a[0].empty()) {
      return 0;
    }
    const int m = a.size();
    const int n = a[0].size();
    vector<vector<int>> dp(n, vector<int>(4, 0));
    int res = 0;
    int last_diag = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (a[i][j] == 1) {
          dp[j][0] = j > 0 ? dp[j - 1][0] + 1 : 1;
          dp[j][1]++;
          int tmp = dp[j][2];
          dp[j][2] = j > 0 ? last_diag + 1 : 1;
          last_diag = tmp;
          dp[j][3] = j < n - 1 ? dp[j + 1][3] + 1 : 1;
          for (int k = 0; k < 4; k++) {
            res = max(res, dp[j][k]);
          }
        } else {
          dp[j][0] = dp[j][1] = dp[j][3] = 0;
          last_diag = dp[j][2];
          dp[j][2] = 0;
        }
      }
    }
    return res;
  }
};

// AC. dp. v2
class Solution {
 public:
  int longestLine(vector<vector<int>>& a) {
    if (a.empty() || a[0].empty()) {
      return 0;
    }
    const int m = a.size();
    const int n = a[0].size();
    vector<int> dp_row(n, 0);
    vector<int> dp_col(n, 0);
    vector<int> dp_diag(m + n - 1, 0);
    vector<int> dp_anti_diag(m + n - 1, 0);
    int res = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        const int diag = j - i + (m - 1);
        const int anti_diag = i + j;
        if (a[i][j] == 1) {
          dp_row[j] = j > 0 ? dp_row[j - 1] + 1 : 1;
          res = max(res, dp_row[j]);
          dp_col[j]++;
          res = max(res, dp_col[j]);
          dp_diag[diag]++;
          res = max(res, dp_diag[diag]);
          dp_anti_diag[anti_diag]++;
          res = max(res, dp_anti_diag[anti_diag]);
        } else {
          dp_row[j] = 0;
          dp_col[j] = 0;
          dp_diag[diag] = 0;
          dp_anti_diag[anti_diag] = 0;
        }
      }
    }
    return res;
  }
};
