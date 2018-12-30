
class Solution {
 public:
  vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
    vector<vector<int>> res;
    if (A.empty() || A[0].empty() || B.empty() || B[0].empty()) {
      return res;
    }
    res.resize(A.size(), vector<int>(B[0].size()));
    unordered_map<int, int> A_col_idx_and_val;
    vector<unordered_map<int, int>> B_col_non_zero_row_idx_and_val(B[0].size());
    for (int j = 0; j < B[0].size(); j++) {
      auto& row_idx_and_val = B_col_non_zero_row_idx_and_val[j];
      for (int i = 0; i < B.size(); i++) {
        if (B[i][j] != 0) {
          row_idx_and_val.emplace(i, B[i][j]);
        }
      }
    }
    for (int i = 0; i < A.size(); i++) {
      A_col_idx_and_val.clear();
      for (int j = 0; j < A[0].size(); j++) {
        if (A[i][j] != 0) {
          A_col_idx_and_val.emplace(j, A[i][j]);
        }
      }
      if(A_col_idx_and_val.empty()) {
        continue;
      }
      for (int j = 0; j < B[0].size(); j++) {
        long sum = 0;
        auto& B_row_idx_and_val = B_col_non_zero_row_idx_and_val[j];
        for (auto& col_idx_and_val : A_col_idx_and_val) {
          if (B_row_idx_and_val.find(col_idx_and_val.first) != B_row_idx_and_val.end()) {
            sum += (col_idx_and_val.second * B_row_idx_and_val[col_idx_and_val.first]);
          }
        }
        res[i][j] = sum;
      }
    }
    return res;
  }
};

class Solution {
 public:
  vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
    vector<vector<int>> res;
    if (A.empty() || A[0].empty() || B.empty() || B[0].empty()) {
      return res;
    }
    res.resize(A.size(), vector<int>(B[0].size()));
    unordered_map<int, int> A_col_idx_and_val;
    vector<unordered_map<int, int>> B_col_non_zero_row_idx_and_val(B[0].size());
    for (int j = 0; j < B[0].size(); j++) {
      auto& row_idx_and_val = B_col_non_zero_row_idx_and_val[j];
      for (int i = 0; i < B.size(); i++) {
        if (B[i][j] != 0) {
          row_idx_and_val.emplace(i, B[i][j]);
        }
      }
    }
    for (int i = 0; i < A.size(); i++) {
      A_col_idx_and_val.clear();
      for (int j = 0; j < A[0].size(); j++) {
        if (A[i][j] != 0) {
          A_col_idx_and_val.emplace(j, A[i][j]);
        }
      }
      if(A_col_idx_and_val.empty()) {
        continue;
      }
      for (int j = 0; j < B[0].size(); j++) {
        long sum = 0;
        auto& B_row_idx_and_val = B_col_non_zero_row_idx_and_val[j];
        for (auto& col_idx_and_val : A_col_idx_and_val) {
          if (B_row_idx_and_val.find(col_idx_and_val.first) != B_row_idx_and_val.end()) {
            sum += (col_idx_and_val.second * B_row_idx_and_val[col_idx_and_val.first]);
          }
        }
        res[i][j] = sum;
      }
    }
    return res;
  }
};

