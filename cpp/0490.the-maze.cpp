// Wrong understanding.
class Solution {
 public:
  typedef pair<int, int> Coord;
  bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    if (maze.empty() || maze[0].empty()) {
      return false;
    }
    const int m = maze.size();
    const int n = maze[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    Coord start_pt(start[0], start[1]);
    Coord dest_pt(destination[0], destination[1]);
    int ex = dest_pt.first;
    int ey = dest_pt.second;
    bool horizon_stop = true, vertical_stop = true;
    bool vertical_no_way =
        ((ex == 0 || maze[ex - 1][ey] == 1) && (ex == m - 1 || maze[ex + 1][ey] == 1));
    bool horizon_no_way =
        ((ey == 0 || maze[ex][ey - 1] == 1) && (ey == n - 1 || maze[ex][ey + 1] == 1));
    if (ey != 0) {
      if (ey != n - 1) {
        if ((maze[ex][ey - 1] == 0) && (maze[ex][ey + 1] == 0)) {
          horizon_stop = false;
        } else if ((maze[ex][ey - 1] == 1) && (maze[ex][ey + 1] == 1)) {
          horizon_stop = false;
        }
      } else {
        if (maze[ex][ey - 1] == 1) {
          horizon_stop = false;
        } else {
          if (!vertical_no_way) {
            horizon_stop = false;
          }
        }
      }
    } else {
      if (ey != n - 1) {
        if (maze[ex][ey + 1] == 1) {
          horizon_stop = false;
        } else {
          if (!vertical_no_way) {
            horizon_stop = false;
          }
        }
      } else {
        horizon_stop = false;
      }
    }
    if (ex != 0) {
      if (ex != m - 1) {
        if ((maze[ex - 1][ey] == 0) && (maze[ex + 1][ey] == 0)) {
          vertical_stop = false;
        } else if ((maze[ex - 1][ey] == 1) && (maze[ex + 1][ey] == 1)) {
          vertical_stop = false;
        }
      } else {
        if (maze[ex - 1][ey] == 1) {
          vertical_stop = false;
        } else {
          if (!horizon_no_way) {
            vertical_stop = false;
          }
        }
      }
    } else {
      if (ex != m - 1) {
        if (maze[ex + 1][ey] == 1) {
          vertical_stop = false;
        } else {
          if (!horizon_no_way) {
            vertical_stop = false;
          }
        }
      } else {
        vertical_stop = false;
      }
    }
    if (!horizon_stop && !vertical_stop) {
      return false;
    }
    /*
    bool can_left = false, can_right = false, can_up = false, can_down = false;
    if (dest_pt.second != 0 && maze[dest_pt.first][dest_pt.second - 1] == 0) {
      can_left = true;
    }
    if (dest_pt.second != n - 1 && maze[dest_pt.first][dest_pt.second + 1] == 0) {
      can_right = true;
    }
    if (dest_pt.first != 0 && maze[dest_pt.first - 1][dest_pt.second] == 0) {
      can_up = true;
    }
    if (dest_pt.first != m - 1 && maze[dest_pt.first + 1][dest_pt.second] == 0) {
      can_down = true;
    }
    bool not_stop =
        ((can_left == true) + (can_right == true) + (can_up == true) + (can_down == true)) > 1;
    if (not_stop) {
      return false;
    }
    */

    /*
    bool block_left = false, block_right = false, block_up = false, block_down = false;
    bool horizontal_one_block = true, vertical_one_block = true;
    if (dest_pt.second == 0 || dest_pt.second == n - 1) {
      horizontal_one_block = false;
    }
    if (dest_pt.first == 0 || dest_pt.first == m - 1) {
      vertical_one_block = false;
    }
    if (dest_pt.second != 0 && maze[dest_pt.first][dest_pt.second - 1] == 1) {
      block_left = true;
    }
    if (dest_pt.second != n - 1 && maze[dest_pt.first][dest_pt.second + 1] == 1) {
      block_right = true;
    }
    if (dest_pt.first != 0 && maze[dest_pt.first - 1][dest_pt.second] == 1) {
      block_up = true;
    }
    if (dest_pt.first != m - 1 && maze[dest_pt.first + 1][dest_pt.second] == 1) {
      block_down = true;
    }
    //      if(block_left&&block_right&&block_up&&block_down) {
    //        return false;
    //      }
    //      if( block_left && block_right && !block_up && !block_down ) {
    //        return false;
    //      }
    //      if( !block_left && !block_right && block_up && block_down ) {
    //        return false;
    //      }
    //      if( !block_left && !block_right && !block_up && !block_down ) {
    //        return false;
    //      }
    horizontal_one_block =
        horizontal_one_block && ((block_left && !block_right) || (!block_left && block_right));
    vertical_one_block =
        vertical_one_block && ((block_up && !block_down) || (!block_up && block_down));
    if (!horizontal_one_block && !vertical_one_block) {
      return false;
    }
    */

    vector<Coord> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, +1}};

    queue<Coord> q;
    q.push(start_pt);
    visited[start_pt.first][start_pt.second] = true;
    while (!q.empty()) {
      int len = q.size();
      for (int i = 0; i < len; i++) {
        Coord& cur = q.front();
        q.pop();
        for (auto& dir : dirs) {
          int x = cur.first + dir.first;
          int y = cur.second + dir.second;
          if (x < 0 || x >= m || y < 0 || y >= n) {
            continue;
          }
          if (!visited[x][y] && maze[x][y] == 0) {
            Coord next(x, y);
            if (next == dest_pt) {
              return true;
            }
            visited[x][y] = true;
            q.push(next);
          }
        }
      }
    }

    return false;
  }
};

// AC. BFS
class Solution {
 public:
  typedef pair<int, int> Coord;
  bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    if (maze.empty() || maze[0].empty()) {
      return false;
    }
    const int m = maze.size();
    const int n = maze[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    Coord start_pt(start[0], start[1]);
    Coord dest_pt(destination[0], destination[1]);

    vector<Coord> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, +1}};

    queue<Coord> q;
    q.push(start_pt);
    visited[start_pt.first][start_pt.second] = true;
    while (!q.empty()) {
      int len = q.size();
      for (int i = 0; i < len; i++) {
        Coord& cur = q.front();
        q.pop();
        for (auto& dir : dirs) {
          int dx = dir.first;
          int dy = dir.second;
          int x = cur.first + dx;
          int y = cur.second + dy;
          if (x < 0 || x >= m || y < 0 || y >= n || maze[x][y] == 1) {
            continue;
          }
          while (x + dx >= 0 && x + dx < m && y + dy >= 0 && y + dy < n &&
                 maze[x + dx][y + dy] == 0) {
            x += dx;
            y += dy;
          }
          if (!visited[x][y]) {  //  && maze[x][y] == 0
            Coord next(x, y);
            if (next == dest_pt) {
              return true;
            }
            visited[x][y] = true;
            q.push(next);
          }
        }
      }
    }

    return false;
  }
};

// AC. DFS
class Solution {
 public:
  typedef pair<int, int> Coord;
  bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    if (maze.empty() || maze[0].empty()) {
      return false;
    }
    const int m = maze.size();
    const int n = maze[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    Coord start_pt(start[0], start[1]);
    Coord dest_pt(destination[0], destination[1]);
    return dfs(maze, start_pt, dest_pt, visited);
  }
  bool dfs(const vector<vector<int>>& maze, const Coord& start, const Coord& dest,
           vector<vector<bool>>& visited) {
    if (visited[start.first][start.second]) {
      return false;
    }
    if (start == dest) {
      return true;
    }
    visited[start.first][start.second] = true;
    vector<Coord> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, +1}};
    const int m = maze.size();
    const int n = maze[0].size();
    for (auto& dir : dirs) {
      int dx = dir.first;
      int dy = dir.second;
      int x = start.first + dx;
      int y = start.second + dy;
      while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
        x += dx;
        y += dy;
      }
      x -= dx;
      y -= dy;
      Coord next(x, y);
      bool ret = dfs(maze, next, dest, visited);
      if (ret) {
        return true;
      }
    }
    return false;
  }
};

