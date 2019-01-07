// Wrong Answer.
class Solution {
 public:
  int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    if (maze.empty() || maze[0].empty()) {
      return 0;
    }
    const int m = maze.size();
    const int n = maze[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    queue<vector<int>> q;
    vector<int> start_pt_step = start;
    start_pt_step.push_back(0);
    q.push(start_pt_step);
    visited[start[0]][start[1]] = true;
    int step = 1;
    vector<int> dx{-1, 1, 0, 0};
    vector<int> dy{0, 0, -1, 1};
    int min_step = -1;
    while (!q.empty()) {
      int len = q.size();
      for (int k = 0; k < len; k++) {
        auto cur = q.front();
        int cur_step = cur[2];
        q.pop();
        for (int i = 0; i < 4; i++) {
          int next_step = cur_step;
          int x = cur[0] + dx[i];
          int y = cur[1] + dy[i];
          while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
            next_step++;
            x += dx[i];
            y += dy[i];
          }
          x -= dx[i];
          y -= dy[i];
          if (maze[x][y] == 0 && !visited[x][y]) {
            vector<int> next;
            next.push_back(x);
            next.push_back(y);
            if (next == destination) {
              if (min_step < 0) {
                min_step = next_step;
              } else {
                min_step = min(min_step, next_step);
              }
              continue;
              // return step;
            }
            next.push_back(next_step);
            visited[x][y] = true;
            q.push(next);
          }
        }
      }
      step++;
    }
    return min_step;
  }
};

// AC. BFS.
class Solution {
 public:
  int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    if (maze.empty() || maze[0].empty()) {
      return 0;
    }
    const int m = maze.size();
    const int n = maze[0].size();
    vector<vector<int>> visited_step(m, vector<int>(n, -1));
    queue<vector<int>> q;
    vector<int> start_pt_step = start;
    start_pt_step.push_back(0);
    q.push(start_pt_step);
    visited_step[start[0]][start[1]] = 0;
    int step = 1;
    vector<int> dx{-1, 1, 0, 0};
    vector<int> dy{0, 0, -1, 1};
    int min_step = -1;
    while (!q.empty()) {
      int len = q.size();
      for (int k = 0; k < len; k++) {
        auto cur = q.front();
        int cur_step = cur[2];
        q.pop();
        for (int i = 0; i < 4; i++) {
          int next_step = cur_step;
          int x = cur[0] + dx[i];
          int y = cur[1] + dy[i];
          while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
            next_step++;
            x += dx[i];
            y += dy[i];
          }
          x -= dx[i];
          y -= dy[i];
          if (maze[x][y] == 0 && (visited_step[x][y] < 0 || visited_step[x][y] > next_step)) {
            vector<int> next;
            next.push_back(x);
            next.push_back(y);
            if (next == destination) {
              if (min_step < 0) {
                min_step = next_step;
              } else {
                min_step = min(min_step, next_step);
              }
              continue;
              // return step;
            }
            next.push_back(next_step);
            visited_step[x][y] = next_step;
            q.push(next);
          }
        }
      }
      step++;
    }
    return min_step;
  }
};

// AC. DFS
class Solution {
 public:
  void dfs(const vector<vector<int>>& maze, const vector<int>& cur, const vector<int>& destination,
           vector<vector<int>>& visited_step, int step, int& min_step) {
    if (cur == destination) {
      if (min_step < 0) {
        min_step = step;
      } else {
        min_step = min(min_step, step);
      }
      return;
    }
    visited_step[cur[0]][cur[1]] = step;
    vector<int> dx{-1, 1, 0, 0};
    vector<int> dy{0, 0, -1, 1};
    const int m = maze.size();
    const int n = maze[0].size();
    for (int i = 0; i < 4; i++) {
      int next_step = step;
      int x = cur[0] + dx[i];
      int y = cur[1] + dy[i];
      while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
        next_step++;
        x += dx[i];
        y += dy[i];
      }
      x -= dx[i];
      y -= dy[i];
      if (maze[x][y] == 0 && (visited_step[x][y] < 0 || visited_step[x][y] > next_step)) {
        vector<int> next{x, y};
        dfs(maze, next, destination, visited_step, next_step, min_step);
      }
    }
  }
  int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    if (maze.empty() || maze[0].empty()) {
      return 0;
    }
    const int m = maze.size();
    const int n = maze[0].size();
    vector<vector<int>> visited_step(m, vector<int>(n, -1));
    int min_step = -1;
    dfs(maze, start, destination, visited_step, 0, min_step);
    return min_step;
  }
};
