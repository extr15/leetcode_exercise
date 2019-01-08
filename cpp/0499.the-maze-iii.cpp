// AC. BFS.
class Solution {
 public:
  struct Node {
    Node(int _x, int _y, int _step = 0, string _path = "")
        : x(_x), y(_y), step(_step), path_str(_path){};
    int x;
    int y;
    int step;
    string path_str;
  };
  string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
    const string impossible("impossible");
    if (maze.empty() || maze[0].empty()) {
      return impossible;
    }
    const int m = maze.size();
    const int n = maze[0].size();
    queue<Node> q;
    Node start(ball[0], ball[1]);
    q.push(start);
    vector<vector<int>> visited_step(m, vector<int>(n, -1));
    visited_step[start.x][start.y] = 0;
    vector<vector<string>> visited_path(m, vector<string>(n, ""));
    vector<int> dx{-1, 0, 1, 0};
    vector<int> dy{0, -1, 0, 1};
    vector<char> dir_str{'u', 'l', 'd', 'r'};
    int hole_step = -1;
    string hole_path("");
    while (!q.empty()) {
      Node cur = q.front();
      q.pop();
      for (int i = 0; i < 4; i++) {
        int x = cur.x + dx[i];
        int y = cur.y + dy[i];
        string next_path = cur.path_str + dir_str[i];
        int next_step = cur.step;
        bool find_hole = false;
        while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
          next_step++;
          if (x == hole[0] && y == hole[1]) {
            find_hole = true;
            if (hole_step < 0) {
              hole_step = next_step;
              hole_path = next_path;
            } else if (hole_step == next_step) {
              hole_step = next_step;
              if (next_path < hole_path) {
                hole_path = next_path;
              }
            } else if (hole_step > next_step) {
              hole_step = next_step;
              hole_path = next_path;
            }
            break;
          }
          x += dx[i];
          y += dy[i];
        }
        if (find_hole) {
          continue;
        }
        x -= dx[i];
        y -= dy[i];
        if (maze[x][y] == 0 &&
            (visited_step[x][y] < 0 || next_step < visited_step[x][y] ||
             (next_step == visited_step[x][y] && next_path < visited_path[x][y]))) {
          visited_step[x][y] = next_step;
          visited_path[x][y] = next_path;
          Node next(x, y, next_step, next_path);
          q.push(next);
        }
      }
    }
    if (hole_step < 0) {
      return impossible;
    } else {
      return hole_path;
    }
  }
};

// AC. BFS. version 2.
class Solution {
 public:
  struct Node {
    Node(int _x, int _y, int _step = 0, string _path = "")
        : x(_x), y(_y), step(_step), path_str(_path){};
    int x;
    int y;
    int step;
    string path_str;
  };
  string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
    const string impossible("impossible");
    if (maze.empty() || maze[0].empty()) {
      return impossible;
    }
    const int m = maze.size();
    const int n = maze[0].size();
    queue<Node> q;
    Node start(ball[0], ball[1]);
    q.push(start);
    vector<vector<int>> visited_step(m, vector<int>(n, -1));
    visited_step[start.x][start.y] = 0;
    vector<vector<string>> visited_path(m, vector<string>(n, ""));
    vector<int> dx{-1, 0, 1, 0};
    vector<int> dy{0, -1, 0, 1};
    vector<char> dir_str{'u', 'l', 'd', 'r'};
    int hole_step = -1;
    string hole_path("");
    while (!q.empty()) {
      Node cur = q.front();
      q.pop();
      if (visited_step[cur.x][cur.y] > 0 && cur.step > visited_step[cur.x][cur.y]) {
        continue;
      }
      for (int i = 0; i < 4; i++) {
        int x = cur.x + dx[i];
        int y = cur.y + dy[i];
        string next_path = cur.path_str + dir_str[i];
        int next_step = cur.step;
        bool find_hole = false;
        while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
          next_step++;
          if (x == hole[0] && y == hole[1]) {
            find_hole = true;
            if (hole_step < 0) {
              hole_step = next_step;
              hole_path = next_path;
            } else if (hole_step == next_step) {
              hole_step = next_step;
              if (next_path < hole_path) {
                hole_path = next_path;
              }
            } else if (hole_step > next_step) {
              hole_step = next_step;
              hole_path = next_path;
            }
            break;
          }
          x += dx[i];
          y += dy[i];
        }
        if (find_hole) {
          continue;
        }
        x -= dx[i];
        y -= dy[i];
        if (maze[x][y] == 0 &&
            (visited_step[x][y] < 0 || next_step < visited_step[x][y] ||
             (next_step == visited_step[x][y] && next_path < visited_path[x][y]))) {
          visited_step[x][y] = next_step;
          visited_path[x][y] = next_path;
          Node next(x, y, next_step, next_path);
          q.push(next);
        }
      }
    }
    if (hole_step < 0) {
      return impossible;
    } else {
      return hole_path;
    }
  }
};

// AC. BFS. version 3.
class Solution {
 public:
  struct Node {
    Node(int _x, int _y, int _step = 0, string _path = "")
        : x(_x), y(_y), step(_step), path_str(_path){};
    int x;
    int y;
    int step;
    string path_str;
  };
  string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
    const string impossible("impossible");
    if (maze.empty() || maze[0].empty()) {
      return impossible;
    }
    const int m = maze.size();
    const int n = maze[0].size();
    queue<Node> q;
    Node start(ball[0], ball[1]);
    q.push(start);
    vector<vector<int>> visited_step(m, vector<int>(n, -1));
    visited_step[start.x][start.y] = -1;
    vector<vector<string>> visited_path(m, vector<string>(n, ""));
    vector<int> dx{-1, 0, 1, 0};
    vector<int> dy{0, -1, 0, 1};
    vector<char> dir_str{'u', 'l', 'd', 'r'};
    int hole_step = -1;
    string hole_path("");
    while (!q.empty()) {
      Node cur = q.front();
      q.pop();
      if (visited_step[cur.x][cur.y] >= 0 &&
          (cur.step > visited_step[cur.x][cur.y] || (cur.step == visited_step[cur.x][cur.y] &&
                                                     cur.path_str >= visited_path[cur.x][cur.y]))) {
        continue;
      }
      visited_step[cur.x][cur.y] = cur.step;
      visited_path[cur.x][cur.y] = cur.path_str;
      for (int i = 0; i < 4; i++) {
        int x = cur.x + dx[i];
        int y = cur.y + dy[i];
        string next_path = cur.path_str + dir_str[i];
        int next_step = cur.step;
        bool find_hole = false;
        while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
          next_step++;
          if (x == hole[0] && y == hole[1]) {
            find_hole = true;
            if (hole_step < 0) {
              hole_step = next_step;
              hole_path = next_path;
            } else if (hole_step == next_step) {
              hole_step = next_step;
              if (next_path < hole_path) {
                hole_path = next_path;
              }
            } else if (hole_step > next_step) {
              hole_step = next_step;
              hole_path = next_path;
            }
            break;
          }
          x += dx[i];
          y += dy[i];
        }
        if (find_hole) {
          continue;
        }
        x -= dx[i];
        y -= dy[i];
        // can just use `if (maze[x][y] == 0 )` .
        if (maze[x][y] == 0 &&
            (visited_step[x][y] < 0 || next_step < visited_step[x][y] ||
             (next_step == visited_step[x][y] && next_path < visited_path[x][y]))) {
          // visited_step[x][y] = next_step; must not set here.
          // visited_path[x][y] = next_path;
          Node next(x, y, next_step, next_path);
          q.push(next);
        }
      }
    }
    if (hole_step < 0) {
      return impossible;
    } else {
      return hole_path;
    }
  }
};

// AC. Dijkstra.
class Solution {
 public:
  struct Node {
    Node(int _x, int _y, int _step = 0, string _path = "")
        : x(_x), y(_y), step(_step), path_str(_path){};
    int x;
    int y;
    int step;
    string path_str;
    bool operator<(const Node& rhs) const {
      if (this->step != rhs.step) {
        return this->step > rhs.step;
      } else {
        return this->path_str > rhs.path_str;
      }
    }
  };
  string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
    const string impossible("impossible");
    if (maze.empty() || maze[0].empty()) {
      return impossible;
    }
    const int m = maze.size();
    const int n = maze[0].size();
    vector<int> dx{-1, 0, 1, 0};
    vector<int> dy{0, -1, 0, 1};
    vector<char> dir_str{'u', 'l', 'd', 'r'};
    priority_queue<Node> pq;
    Node start(ball[0], ball[1]);
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    pq.push(start);
    while (!pq.empty()) {
      Node cur = pq.top();
      pq.pop();
      if (cur.x == hole[0] && cur.y == hole[1]) {
        return cur.path_str;
      }
      if (visited[cur.x][cur.y]) {
        continue;
      }
      visited[cur.x][cur.y] = true;
      for (int i = 0; i < 4; i++) {
        int x = cur.x + dx[i];
        int y = cur.y + dy[i];
        string next_path = cur.path_str + dir_str[i];
        int next_step = cur.step;
        bool find_hole = false;
        while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
          next_step++;
          if (x == hole[0] && y == hole[1]) {
            find_hole = true;
            break;
          }
          x += dx[i];
          y += dy[i];
        }
        if (!find_hole) {
          x -= dx[i];
          y -= dy[i];
        }
        if (maze[x][y] == 0 && !visited[x][y]) {
          Node next(x, y, next_step, next_path);
          pq.push(next);
        }
      }
    }
    return impossible;
  }
};

// AC. dijkstra. v2.
class Solution {
 public:
  struct Node {
    Node(int _x, int _y, int _step = 0, string _path = "")
        : x(_x), y(_y), step(_step), path_str(_path){};
    int x;
    int y;
    int step;
    string path_str;
  };
  struct NodeCmp {
    bool operator()(const Node& lhs, const Node& rhs) const {
      if (lhs.step != rhs.step) {
        return lhs.step > rhs.step;
      } else {
        return lhs.path_str > rhs.path_str;
      }
    }
  };
  string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
    const string impossible("impossible");
    if (maze.empty() || maze[0].empty()) {
      return impossible;
    }
    const int m = maze.size();
    const int n = maze[0].size();
    vector<int> dx{-1, 0, 1, 0};
    vector<int> dy{0, -1, 0, 1};
    vector<char> dir_str{'u', 'l', 'd', 'r'};
    priority_queue<Node, vector<Node>, NodeCmp> pq;
    Node start(ball[0], ball[1]);
    vector<vector<int>> visited_step(m, vector<int>(n, -1));
    // important since we set `visited_step` when push it to priority_queue instead of when access it!
    visited_step[start.x][start.y] = 0;
    vector<vector<string>> visited_path(m, vector<string>(n, ""));
    pq.push(start);
    while (!pq.empty()) {
      Node cur = pq.top();
      pq.pop();
      if (cur.x == hole[0] && cur.y == hole[1]) {
        return cur.path_str;
      }
      if (visited_step[cur.x][cur.y] > 0 && cur.step > visited_step[cur.x][cur.y]) {
        continue;
      }
      for (int i = 0; i < 4; i++) {
        int x = cur.x + dx[i];
        int y = cur.y + dy[i];
        string next_path = cur.path_str + dir_str[i];
        int next_step = cur.step;
        bool find_hole = false;
        while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
          next_step++;
          if (x == hole[0] && y == hole[1]) {
            find_hole = true;
            break;
          }
          x += dx[i];
          y += dy[i];
        }
        if (!find_hole) {
          x -= dx[i];
          y -= dy[i];
        }
        if (maze[x][y] != 0) {
          continue;
        }
        if (visited_step[x][y] < 0 ||
            (next_step < visited_step[x][y] ||
             (next_step == visited_step[x][y] && next_path < visited_path[x][y]))) {
          visited_step[x][y] = next_step;
          visited_path[x][y] = next_path;
          Node next(x, y, next_step, next_path);
          pq.push(next);
        }
      }
    }
    return impossible;
  }
};


#include <iostream>

int main(int argc, char *argv[]) {
//[[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]]
//[4,3]
//[0,1]  
    return 0;
}
