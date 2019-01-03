// Failed.
class Solution {
 public:
  bool validTree(int n, vector<pair<int, int>>& edges) {
    vector<vector<bool>> connect(n, vector<bool>(n, false));
    for (auto& e : edges) {
      connect[e.first][e.second] = true;
      connect[e.second][e.first] = true;
    }
    vector<int> visited(n, 0);
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      for (int i = 0; i < n; i++) {
        if (i == cur) {
          continue;
        }
        if (connect[cur][i]) {
          if (visited[i] == 2) {
            continue;
          }
          if (visited[i] == 1) {
            return false;
          }
          q.push(i);
          visited[i] = 1;
        }
      }
      visited[cur] = 2;
    }
    for (auto v : visited) {
      if (v == 0) {
        return false;
      }
    }
    return true;
  }
};
