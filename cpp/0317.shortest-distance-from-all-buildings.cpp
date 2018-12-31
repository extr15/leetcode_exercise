// Wrong 1.
class Solution {
 public:
  typedef pair<int, int> Coord;
  int shortestDistance(vector<vector<int>>& grid) {
    const int m = grid.size();
    if (m == 0) {
      return -1;
    }
    const int n = grid[0].size();
    if (n == 0) {
      return -1;
    }
    queue<Coord> q;
    queue<int> q_id;
    int id = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          q.push({i, j});
          q_id.push(id++);
        }
      }
    }
    const int building_num = q.size();
    vector<vector<unordered_set<int>>> visited(m, vector<unordered_set<int>>(n));
    vector<vector<vector<int>>> dist(m, vector<vector<int>>(n, vector<int>(building_num)));
    int cur_dist = 1;
    vector<Coord> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool find_target = false;
    while (!q.empty() && !find_target) {
      int len = q.size();
      for (int i = 0; i < len; i++) {
        Coord& cur = q.front();
        int cur_id = q_id.front();
        if(visited[cur.first][cur.second].size() == building_num) {
          find_target = true;
          break;
        }
        q.pop();
        q_id.pop();
        for (int j = 0; j < 4; j++) {
          int x = cur.first + dirs[j].first;
          int y = cur.second + dirs[j].second;
          if (x < 0 || x >= m || y < 0 || y >= n) {
            continue;
          }
          if (grid[x][y] == 2 || grid[x][y] == 1) {
            continue;
          }
          if (visited[x][y].find(cur_id) == visited[x][y].end()) {
            visited[x][y].insert(cur_id);
            q.push({x, y});
            q_id.push(cur_id);
            dist[x][y][cur_id] = cur_dist;
//            if (visited[x][y].size() == building_num) {
//              find_target = true;
//              break;
//            }
          }
        }
//        if (find_target) {
//          break;
//        }
      }
      cur_dist++;
    }
    if (find_target) {
      //Coord& target = q.back();
      Coord& target = q.front();
      int x = target.first;
      int y = target.second;
      int sum_dist = 0;
      for (int i = 0; i < building_num; i++) {
        sum_dist += dist[x][y][i];
      }
      return sum_dist;
    } else {
      return -1;
    }
  }
};

// Wrong 2.
class Solution {
 public:
  typedef pair<int, int> Coord;
  int shortestDistance(vector<vector<int>>& grid) {
    const int m = grid.size();
    if (m == 0) {
      return -1;
    }
    const int n = grid[0].size();
    if (n == 0) {
      return -1;
    }
    queue<Coord> q;
    queue<int> q_id;
    int id = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          q.push({i, j});
          q_id.push(id++);
        }
      }
    }
    const int building_num = q.size();
    vector<vector<unordered_set<int>>> visited(m, vector<unordered_set<int>>(n));
    vector<vector<vector<int>>> dist(m, vector<vector<int>>(n, vector<int>(building_num)));
    int cur_dist = 1;
    vector<Coord> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool find_target = false;
    while (!q.empty() && !find_target) {
      int len = q.size();
      for (int i = 0; i < len; i++) {
        Coord& cur = q.front();
        int cur_id = q_id.front();
        auto& cur_visit =visited[cur.first][cur.second]; 
        const int cur_visited_cnt = cur_visit.size();
        if( (grid[cur.first][cur.second] != 1) && ((cur_visited_cnt == building_num) || (cur_visited_cnt== building_num-1 && cur_visit.find(cur_id) == cur_visit.end()))  ){
          find_target = true;
          break;
        }
        q.pop();
        q_id.pop();
        if(visited[cur.first][cur.second].find(cur_id) != visited[cur.first][cur.second].end()) {
          continue;
        }
        visited[cur.first][cur.second].insert(cur_id);
        for (int j = 0; j < 4; j++) {
          int x = cur.first + dirs[j].first;
          int y = cur.second + dirs[j].second;
          if (x < 0 || x >= m || y < 0 || y >= n) {
            continue;
          }
          if (grid[x][y] == 2 || grid[x][y] == 1) {
            continue;
          }
          if (visited[x][y].find(cur_id) == visited[x][y].end()) {
            //visited[x][y].insert(cur_id);
            q.push({x, y});
            q_id.push(cur_id);
            dist[x][y][cur_id] = cur_dist;
//            if (visited[x][y].size() == building_num) {
//              find_target = true;
//              break;
//            }
          }
        }
//        if (find_target) {
//          break;
//        }
      }
      cur_dist++;
    }
    if (find_target) {
      //Coord& target = q.back();
      Coord& target = q.front();
      int x = target.first;
      int y = target.second;
      int sum_dist = 0;
      for (int i = 0; i < building_num; i++) {
        sum_dist += dist[x][y][i];
      }
      return sum_dist;
    } else {
      return -1;
    }
  }
};


// Wrong 3.
class Solution {
 public:
  typedef pair<int, int> Coord;
  int shortestDistance(vector<vector<int>>& grid) {
    const int m = grid.size();
    if (m == 0) {
      return -1;
    }
    const int n = grid[0].size();
    if (n == 0) {
      return -1;
    }
    queue<Coord> q;
    queue<int> q_id;
    int id = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          q.push({i, j});
          q_id.push(id++);
        }
      }
    }
    const int building_num = q.size();
    vector<vector<unordered_set<int>>> visited(m, vector<unordered_set<int>>(n));
    vector<vector<vector<int>>> dist(m, vector<vector<int>>(n, vector<int>(building_num)));
    int cur_dist = 1;
    vector<Coord> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool find_target = false;
    while (!q.empty() && !find_target) {
      int len = q.size();
      for (int i = 0; i < len; i++) {
        Coord& cur = q.front();
        int cur_id = q_id.front();
//        if(visited[cur.first][cur.second].size() == building_num) {
//          find_target = true;
//          break;
//        }
        q.pop();
        q_id.pop();
        for (int j = 0; j < 4; j++) {
          int x = cur.first + dirs[j].first;
          int y = cur.second + dirs[j].second;
          if (x < 0 || x >= m || y < 0 || y >= n) {
            continue;
          }
          if (grid[x][y] == 2 || grid[x][y] == 1) {
            continue;
          }
          if (visited[x][y].find(cur_id) == visited[x][y].end()) {
            visited[x][y].insert(cur_id);
            q.push({x, y});
            q_id.push(cur_id);
            dist[x][y][cur_id] = cur_dist;
            if (visited[x][y].size() == building_num) {
              find_target = true;
              //break;
            }
          }
        }
//        if (find_target) {
//          break;
//        }
      }
      cur_dist++;
    }
    if (find_target) {
      int min_sum_dist = -1;
      while(!q.empty()) {
        //Coord& target = q.back();
        Coord& target = q.front();
        q.pop();
        int x = target.first;
        int y = target.second;
        if(visited[x][y].size() != building_num) {
          continue;
        }
        int sum_dist = 0;
        for (int i = 0; i < building_num; i++) {
          sum_dist += dist[x][y][i];
        }
        if(min_sum_dist < 0) {
          min_sum_dist = sum_dist;
        }
        else {
          min_sum_dist = min(min_sum_dist, sum_dist);
        }
      }
      return min_sum_dist;
    } else {
      return -1;
    }
  }
};
