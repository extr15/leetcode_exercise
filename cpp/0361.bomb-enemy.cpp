class Solution {
 public:
  struct Type {
    Type(int c, int bi, int ei) : enemy_cnt(c), begin_idx(bi), end_idx(ei){};
    int enemy_cnt;
    int begin_idx;
    int end_idx;
  };
  int maxKilledEnemies(vector<vector<char>>& grid) {
    if(grid.empty() || grid[0].empty()) {
      return 0;
    }
    const int m = grid.size();
    const int n = grid[0].size();
    vector<vector<Type>> each_row;
    vector<vector<Type>> each_col;
    each_row.reserve(m);
    each_col.reserve(n);
    for (int i = 0; i < m; i++) {
      vector<Type> tmp;
      int enemy_cnt = 0, begin_idx = 0, end_idx = -1;
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 'W') {
          if (enemy_cnt > 0) {
            tmp.emplace_back(enemy_cnt, begin_idx, j);
            enemy_cnt = 0;
            begin_idx = -1;
          }
          begin_idx = j + 1;
        } else if (grid[i][j] == 'E') {
          enemy_cnt++;
        }
      }
      if(enemy_cnt > 0) {
        tmp.emplace_back(enemy_cnt, begin_idx, n);
      }
      each_row.push_back(tmp);
    }
    for (int j = 0; j < n; j++) {
      vector<Type> tmp;
      int enemy_cnt = 0, begin_idx = 0, end_idx = -1;
      for (int i = 0; i < m; i++) {
        if (grid[i][j] == 'W') {
          if (enemy_cnt > 0) {
            tmp.emplace_back(enemy_cnt, begin_idx, i);
            enemy_cnt = 0;
            begin_idx = -1;
          }
          begin_idx = i + 1;
        } else if (grid[i][j] == 'E') {
          enemy_cnt++;
        }
      }
      if(enemy_cnt > 0) {
        tmp.emplace_back(enemy_cnt, begin_idx, m);
      }
      each_col.push_back(tmp);
    }
    vector<vector<int>> kill_cnt(m, vector<int>(n, 0));
    int max_kill = 0;
    for (int i = 0; i < m; i++) {
      auto& row = each_row[i];
      for (auto elem : row) {
        for (int j = elem.begin_idx; j < elem.end_idx; j++) {
          if(grid[i][j] != '0') {
            continue;
          }
          kill_cnt[i][j] += elem.enemy_cnt;
          max_kill = max(max_kill, kill_cnt[i][j]);
        }
      }
    }
    for (int j = 0; j < n; j++) {
      auto& col = each_col[j];
      for (auto elem : col) {
        for (int i = elem.begin_idx; i < elem.end_idx; i++) {
          if(grid[i][j] != '0') {
            continue;
          }
          kill_cnt[i][j] += elem.enemy_cnt;
          max_kill = max(max_kill, kill_cnt[i][j]);
        }
      }
    }
    return max_kill;
  }
};
