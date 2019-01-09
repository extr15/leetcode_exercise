class NumMatrix {
 public:
  NumMatrix(vector<vector<int>> matrix) : data_(matrix) {
    m = matrix.size();
    if (m == 0) {
      return;
    }
    n = matrix[0].size();
    if (n == 0) {
      return;
    }
    bit_len_ = n + 1;
    bit_vec_.resize(m, vector<long>(bit_len_));
    for (int i = 0; i < m; i++) {
      vector<long>& bit = bit_vec_[i];
      // bit.resize(bit_len_, 0);
      for (int j = 0; j < n; j++) {
        updateBITree(bit, j, matrix[i][j]);
      }
    }
  }
  void updateBITree(vector<long>& bit, int i, int val) {
    i++;
    while (i < bit.size()) {
      bit[i] += val;
      i += (i & (-i));
    }
  }
  long addBITree(vector<long>& bit, int i) {
    i++;
    long sum = 0;
    while (i > 0) {
      sum += bit[i];
      i -= (i & (-i));
    }
    return sum;
  }

  void update(int row, int col, int val) {
    if (m == 0 || n == 0 || row >= m || col >= n) {
      return;
    }
    int delta = val - data_[row][col];
    data_[row][col] = val;
    updateBITree(bit_vec_[row], col, delta);
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    if (m == 0 || n == 0 || row2 >= m || col2 >= n) {
      return 0;
    }
    long sum = 0;
    for (int r = row1; r <= row2; r++) {
      auto& bit = bit_vec_[r];
      sum += (addBITree(bit, col2) - addBITree(bit, col1 - 1));
    }
    return (int)sum;
  }

 private:
  int m, n;
  int bit_len_;
  vector<vector<long>> bit_vec_;
  vector<vector<int>> data_;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */
