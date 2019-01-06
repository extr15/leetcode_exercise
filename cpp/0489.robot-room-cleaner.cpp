/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */
// AC.
class Solution {
 public:
  typedef pair<int, int> Coord;
  struct PairHash {
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U>& x) const {
      return std::hash<T>()(x.first) ^ (std::hash<U>()(x.second) >> 1);
    }
  };
  void dfs(Robot& robot, Coord& cur, int dir, unordered_set<Coord, PairHash>& visited) {
    //    if (visited.find(cur) != visited.end()) {
    //      return;
    //    }
    const vector<Coord> dirs{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    robot.clean();
    visited.insert(cur);
    bool can_move = false;
    for (int i = 0; i < 4; i++) {
      int idx = (dir + i) % 4;
      Coord next;
      next.first = cur.first + dirs[idx].first;
      next.second = cur.second + dirs[idx].second;
      if (visited.find(next) == visited.end()) {
        if (robot.move()) {
          // orders.push(0);
          dfs(robot, next, idx, visited);
          can_move = true;
          robot.turnRight();
          robot.turnRight();
          robot.move();
          robot.turnRight();
          robot.turnRight();
        }
      } else {
        ;
      }
      robot.turnRight();
    }
  }
  void cleanRoom(Robot& robot) {
    unordered_set<Coord, PairHash> visited;
    // stack<int> orders;
    Coord cur(0, 0);
    dfs(robot, cur, 0, visited);
  }
};

// AC.
class Solution {
 public:
  void dfs(Robot& robot, int x, int y, int dir,
           unordered_map<int, unordered_map<int, int>>& visited) {
    if (visited[x][y] == 1) {
      return;
    }
    robot.clean();
    visited[x][y] = 1;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int cur_dir = dir;
    for (int i = 0; i < 4; i++) {
      int x2 = x + dx[cur_dir];
      int y2 = y + dy[cur_dir];
      if (robot.move()) {
        dfs(robot, x2, y2, cur_dir, visited);
        robot.turnRight();
        robot.turnRight();
        robot.move();
        robot.turnRight();
        robot.turnRight();
      }
      robot.turnRight();
      cur_dir = (cur_dir + 1) % 4;
    }
  }
  void cleanRoom(Robot& robot) {
    unordered_map<int, unordered_map<int, int>> visited;
    dfs(robot, 0, 0, 0, visited);
  }
};

