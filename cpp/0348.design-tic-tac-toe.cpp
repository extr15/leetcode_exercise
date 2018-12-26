class TicTacToe {
 public:
  /** Initialize your data structure here. */
  TicTacToe(int n) : n_(n), board_(vector<vector<int>>(n, vector<int>(n, 0))) {}

  /** Player {player} makes a move at ({row}, {col}).
      @param row The row of the board.
      @param col The column of the board.
      @param player The player, can be either 1 or 2.
      @return The current winning condition, can be either:
              0: No one wins.
              1: Player 1 wins.
              2: Player 2 wins. */
  int move(int row, int col, int player) {
    board_[row][col] = player;
    int r = 0;
    for (; r < n_; r++) {
      if (board_[r][col] != player) {
        break;
      }
    }
    if (r == n_) {
      return player;
    }
    int c = 0;
    for (; c < n_; c++) {
      if (board_[row][c] != player) {
        break;
      }
    }
    if (c == n_) {
      return player;
    }
    if (row == col) {
      int r = 0;
      for (; r < n_; r++) {
        if (board_[r][r] != player) {
          break;
        }
      }
      if (r == n_) {
        return player;
      }
    }
    if (row + col == n_ - 1) {
      int r = 0;
      for (; r < n_; r++) {
        if (board_[r][n_ - 1 - r] != player) {
          break;
        }
      }
      if (r == n_) {
        return player;
      }
    }
    return 0;
  }

 private:
  vector<vector<int>> board_;
  int n_;
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe obj = new TicTacToe(n);
 * int param_1 = obj.move(row,col,player);
 */
