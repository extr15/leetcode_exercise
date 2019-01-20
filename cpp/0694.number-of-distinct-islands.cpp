#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  typedef pair<int, int> Coord;
  // Wrong for belowing case A.
  void bfs(const vector<vector<int>>& grid, int r, int c, vector<vector<bool>>& visited,
           string& str) {
    vector<pair<int, int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<char> dir_char{'r', 'd', 'l', 'u'};
    const int m = grid.size();
    const int n = grid[0].size();
    queue<Coord> q;
    q.push({r, c});
    visited[r][c] = true;
    while (!q.empty()) {
      Coord cur = q.front();
      q.pop();
      for (int i = 0; i < 4; i++) {
        int x = cur.first + dirs[i].first;
        int y = cur.second + dirs[i].second;
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0 || visited[x][y]) {
          continue;
        }
        Coord next(x, y);
        q.push(next);
        visited[x][y] = true;
        str += dir_char[i];
      }
    }
  }
  // AC.
  void bfs2(const vector<vector<int>>& grid, int r, int c, vector<vector<bool>>& visited,
            string& str) {
    vector<pair<int, int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<char> dir_char{'r', 'd', 'l', 'u'};
    vector<char> rev_dir_char{'l', 'u', 'r', 'd'};
    const int m = grid.size();
    const int n = grid[0].size();
    queue<Coord> q;
    queue<char> q2;
    q.push({r, c});
    q2.push('0');
    visited[r][c] = true;
    while (!q.empty()) {
      Coord cur = q.front();
      q.pop();
      str += q2.front();
      q2.pop();
      for (int i = 0; i < 4; i++) {
        int x = cur.first + dirs[i].first;
        int y = cur.second + dirs[i].second;
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0 || visited[x][y]) {
          continue;
        }
        Coord next(x, y);
        q.push(next);
        q2.push(rev_dir_char[i]);  // must be `rev_dir_char`, otherwise use `dir_char` can not pass.
        // `dir_char` is wrong for `0694.number-of-distinct-islands.data.1.txt`
        visited[x][y] = true;
        str += dir_char[i];
      }
    }
  }

  // AC.
  void dfsRecursive(const vector<vector<int>>& grid, int r, int c, vector<vector<bool>>& visited,
                    string& str) {
    vector<pair<int, int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<char> dir_char{'r', 'd', 'l', 'u'};
    vector<char> rev_dir_char{'l', 'u', 'r', 'd'};
    const int m = grid.size();
    const int n = grid[0].size();
    visited[r][c] = true;

    for (int i = 0; i < 4; i++) {
      int x = r + dirs[i].first;
      int y = c + dirs[i].second;
      if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0 || visited[x][y]) {
        continue;
      }
      str += dir_char[i];
      dfsRecursive(grid, x, y, visited, str);
      str += rev_dir_char[i];  // it is OK to use `dir_char`.
    }
  }
  // Wrong for `0694.number-of-distinct-islands.data.2.txt`.
  void dfsIterative(const vector<vector<int>>& grid, int r, int c, vector<vector<bool>>& visited,
                    string& str) {
    vector<pair<int, int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<char> dir_char{'r', 'd', 'l', 'u'};
    vector<char> rev_dir_char{'l', 'u', 'r', 'd'};
    const int m = grid.size();
    const int n = grid[0].size();
    visited[r][c] = true;
    stack<Coord> k;
    stack<char> k2;
    k.push({r, c});
    k2.push('0');
    while (!k.empty()) {
      Coord cur = k.top();
      k.pop();
      str += k2.top();
      k2.pop();
      for (int i = 0; i < 4; i++) {
        int x = cur.first + dirs[i].first;
        int y = cur.second + dirs[i].second;
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0 || visited[x][y]) {
          continue;
        }
        visited[x][y] = true;
        k.push({x, y});
        //k2.push(rev_dir_char[i]); // Wrong for case B.
        k2.push(dir_char[i]);
        str += dir_char[i];
      }
    }
  }

  // AC. slightly slow.
  void dfsIterative2(const vector<vector<int>>& grid, int r, int c, vector<vector<bool>>& visited,
                    string& str) {
    vector<pair<int, int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<char> dir_char{'r', 'd', 'l', 'u'};
    vector<char> rev_dir_char{'l', 'u', 'r', 'd'};
    const int m = grid.size();
    const int n = grid[0].size();
    visited[r][c] = true;
    stack<Coord> k;
    stack<char> k2;
    k.push({r, c});
    k2.push('0');
    while (!k.empty()) {
      Coord cur = k.top();
      //k.pop();
      str += k2.top();
      //k2.pop();
      bool have_new_neighbor = false;
      for (int i = 0; i < 4; i++) {
        int x = cur.first + dirs[i].first;
        int y = cur.second + dirs[i].second;
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0 || visited[x][y]) {
          continue;
        }
        have_new_neighbor = true;
        visited[x][y] = true;
        k.push({x, y});
        k2.push(rev_dir_char[i]);
        //k2.push(dir_char[i]);
        str += dir_char[i];
      }
      if(!have_new_neighbor) {
        k.pop();
        k2.pop();
      }
    }
  }
  int numDistinctIslands(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) {
      return 0;
    }
    const int m = grid.size();
    const int n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    unordered_set<string> islands_str;
    for (int r = 0; r < m; r++) {
      for (int c = 0; c < n; c++) {
        if (grid[r][c] == 1 && !visited[r][c]) {
          string str;
          // bfs(grid, r, c, visited, str);
          // dfsRecursive(grid, r, c, visited, str);
          // bfs2(grid, r, c, visited, str);
          //dfsIterative(grid, r, c, visited, str);
          dfsIterative2(grid, r, c, visited, str);
          //cout << "str: " << str << endl;
          islands_str.insert(str);
        }
      }
    }
    return islands_str.size();
  }
};

/*
// case A:
[ 0, 0, 0, 0, 1, 1, 1 ], [ 1, 1, 1, 1, 1, 1, 1 ], [ 0, 0, 0, 0, 0, 0, 0 ], [ 0, 0, 0, 0, 1, 1, 1 ],
    [ 1, 1, 1, 1, 1, 1, 0 ], [ 0, 0, 0, 1, 0, 0, 0 ]

// case B:
[ [0,1,1],
  [1,1,0],
  [0,0,0],
  [1,1,1],
  [1,0,0]]

  */

int main(int argc, char* argv[]) {
  vector<vector<int>> a{{0, 1, 1}, {1, 1, 0}, {0, 0, 0}, {1, 1, 1}, {1, 0, 0}};
  Solution sol;
  cout << sol.numDistinctIslands(a) << endl;
  return 0;
}

