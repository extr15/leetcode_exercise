class Solution {
 public:
  typedef pair<int, int> Coord;
  vector<Coord> extendCoord(const Coord& cur, int m, int n) {
    vector<Coord> near;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
      int next_x = cur.first + dx[i];
      int next_y = cur.second + dy[i];
      if (next_x >= 0 && next_x < m && next_y >= 0 && next_y < n) {
        near.emplace_back(next_x, next_y);
      }
    }
    return near;
  }
  void bfs(int r, int c, vector<vector<int>>& rooms) {
    const int m = rooms.size();
    const int n = rooms[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    queue<pair<int, int>> q;
    q.emplace(r, c);
    visited[r][c] = true;
    int dist = 0;
    while (!q.empty()) {
      queue<Coord> next_q;
      while (!q.empty()) {
        Coord cur = q.front();
        q.pop();
        rooms[cur.first][cur.second] = dist;
        vector<Coord> near = extendCoord(cur, m, n);
        for (int i = 0; i < near.size(); i++) {
          Coord next = near[i];
          if (rooms[next.first][next.second] != -1 && !visited[next.first][next.second]) {
            visited[next.first][next.second] = true;
            if (dist + 1 < rooms[next.first][next.second]) {
              next_q.push(next);
            }
          }
        }
      }
      q = next_q;
      dist++;
    }
  }
  void wallsAndGates(vector<vector<int>>& rooms) {
    const int m = rooms.size();
    if (m == 0) {
      return;
    }
    const int n = rooms[0].size();
    if (n == 0) {
      return;
    }
    vector<pair<int, int>> zero_coordinate;
    for (int r = 0; r < m; r++) {
      for (int c = 0; c < n; c++) {
        if (rooms[r][c] == 0) {
          zero_coordinate.emplace_back(r, c);
        }
      }
    }
    for (int i = 0; i < zero_coordinate.size(); i++) {
      int r = zero_coordinate[i].first;
      int c = zero_coordinate[i].second;
      bfs(r, c, rooms);
    }
  }
};
