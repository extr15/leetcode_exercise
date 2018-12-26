class Solution {
 public:
  int minTotalDistance(vector<vector<int>>& grid) {
    vector<int> x, y;
    for (int r = 0; r < grid.size(); r++) {
      for (int c = 0; c < grid[0].size(); c++) {
        if (grid[r][c] == 1) {
          x.push_back(r);
          y.push_back(c);
        }
      }
    }
    int mid_idx = x.size() / 2;
    std::nth_element(x.begin(), x.begin() + mid_idx, x.end());
    int mid_x = x[mid_idx];
    int dist_x = 0;
    for (int i = 0; i < x.size(); i++) {
      dist_x += std::abs(x[i] - mid_x);
    }
    std::nth_element(y.begin(), y.begin() + mid_idx, y.end());
    int mid_y = y[mid_idx];
    int dist_y = 0;
    for (int i = 0; i < y.size(); i++) {
      dist_y += std::abs(y[i] - mid_y);
    }
    return (dist_x + dist_y);
  }
};
