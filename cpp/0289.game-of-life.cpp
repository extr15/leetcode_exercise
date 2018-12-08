class Solution {
 public:
  void gameOfLife(vector<vector<int>>& board) {
    if (board.empty()) {
      return;
    }
    const int m = board.size();
    const int n = board[0].size();
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        setBoardVal(board, i, j, m, n);
      }
    }
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (board[i][j] == 2) {
          board[i][j] = 1;
        } else if (board[i][j] == 3) {
          board[i][j] = 0;
        }
      }
    }
  }
  void setBoardVal(vector<vector<int>>& b, int i, int j, int m, int n) {
    int live_cnt = 0;
    for (int p = i - 1; p <= i + 1; p++) {
      for (int q = j - 1; q <= j + 1; q++) {
        if (p == i && q == j) {
          continue;
        }
        if (p < 0 || p >= m || q < 0 || q >= n) {
          continue;
        }
        if (b[p][q] == 1 || b[p][q] == 3) {
          live_cnt++;
        }
      }
    }
    if (b[i][j] == 0) {
      if (live_cnt == 3) {
        b[i][j] = 2;
      }
    } else {
      if (live_cnt < 2 || live_cnt > 3) {
        b[i][j] = 3;
      }
    }
  }
};
