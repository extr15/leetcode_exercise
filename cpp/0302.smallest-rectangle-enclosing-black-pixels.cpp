class Solution {
 public:
  void dfs(vector<vector<char>>& image, int x, int y, int& min_x, int& max_x, int& min_y,
           int& max_y) {
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};
    const int height = image.size();
    const int width = image[0].size();
    for (int i = 0; i < 4; i++) {
      int next_x = x + dx[i];
      int next_y = y + dy[i];
      if (next_x < 0 || next_x >= height || next_y < 0 || next_y >= width) {
        continue;
      }
      if (image[next_x][next_y] == '1') {
        image[next_x][next_y] = '2';
        min_x = min(min_x, next_x);
        max_x = max(max_x, next_x);
        min_y = min(min_y, next_y);
        max_y = max(max_y, next_y);
        dfs(image, next_x, next_y, min_x, max_x, min_y, max_y);
      }
    }
  }
  int minArea(vector<vector<char>>& image, int x, int y) {
    int min_x = x, max_x = x, min_y = y, max_y = y;
    dfs(image, x, y, min_x, max_x, min_y, max_y);
    return (max_x - min_x + 1) * (max_y - min_y + 1);
  }
};
