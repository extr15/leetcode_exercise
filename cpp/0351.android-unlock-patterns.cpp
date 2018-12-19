#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findNextNum(int cur_num, const vector<bool>& visited) {
    vector<int> next_nums;
    /*
    const static vector<vector<int> > near_num{{0},
                                               {2, 4, 5},
                                               {1, 3, 4, 5, 6},
                                               {2, 5, 6},
                                               {1, 2, 5, 7, 8},
                                               {1, 2, 3, 4, 6, 7, 8, 9},
                                               {2, 3, 5, 8, 9},
                                               {4, 5, 8},
                                               {4, 5, 6, 7, 9},
                                               {5, 6, 8}};
    const static vector < vector<vector<int> > > far_num{
                              {{0}},
                              {{3, 2}, {6, 2, 5}, {7, 4}, {8, 4, 5}, {9, 5}},  // 1
                              {{7, 4, 5}, {8, 5}, {9, 5, 6}},                  // 2
                              {{1, 2}, {4, 2, 5}, {7, 5}, {8, 5, 6}, {9, 6}},  // 3
                              {{3, 2, 5}, {6, 5}, {9, 5, 8}},                  // 4
                              {{}},                                            // 5
                              {{1, 2, 5}, {4, 5}, {7, 5, 8}},                  // 6
                              {{1, 4}, {2, 4, 5}, {3, 5}, {6, 5, 8}, {9, 8}},  // 7
                              {{1, 4, 5}, {2, 5}, {3, 5, 6}},                  // 8
                              {{1, 5}, {2, 5, 6}, {3, 6}, {4, 5, 8}, {7, 8}}   // 9
                          };
    */
    const static vector<vector<int> > near_num{{0},
                                               {2, 4, 5, 6, 8},           // 1
                                               {1, 3, 4, 5, 6, 7, 9},     // 2
                                               {2, 5, 6, 4, 8},           // 3
                                               {1, 2, 5, 7, 8, 3, 9},     // 4
                                               {1, 2, 3, 4, 6, 7, 8, 9},  // 5
                                               {2, 3, 5, 8, 9, 1, 7},     // 6
                                               {4, 5, 8, 2, 6},           // 7
                                               {4, 5, 6, 7, 9, 1, 3},     // 8
                                               {5, 6, 8, 4, 2}};          // 9
    const static vector<vector<vector<int> > > far_num{
        {{0}},
        {{3, 2}, {7, 4}, {9, 5}},  // 1
        {{8, 5}},                  // 2
        {{1, 2}, {7, 5}, {9, 6}},  // 3
        {{6, 5}},                  // 4
        {{}},                      // 5
        {{4, 5}},                  // 6
        {{1, 4}, {3, 5}, {9, 8}},  // 7
        {{2, 5}},                  // 8
        {{1, 5}, {3, 6}, {7, 8}}   // 9
    };

    const auto& cur_near_num = near_num[cur_num];
    for (auto near : cur_near_num) {
      if (!visited[near]) {
        next_nums.push_back(near);
      }
    }
    if (cur_num == 5) {
      return next_nums;
    }
    const auto& cur_far_num = far_num[cur_num];
    for (int i = 0; i < cur_far_num.size(); i++) {
      auto& next_and_checks = cur_far_num[i];
      int next_num = next_and_checks[0];
      if(visited[next_num]) {
        continue;
      }
      bool can_pass = true;
      for (int j = 1; j < next_and_checks.size(); j++) {
        if (!visited[next_and_checks[j]]) {
          can_pass = false;
          break;
        }
      }
      if (can_pass) {
        next_nums.push_back(next_num);
      }
    }
    return next_nums;
  }
  int dfs(int cur_num, int left_steps, vector<bool>& visited) {
    if (left_steps == 0) {
      return 1;
    }
    visited[cur_num] = true;
    vector<int> next_nums = findNextNum(cur_num, visited);
    int method_cnt = 0;
    for (int i = 0; i < next_nums.size(); i++) {
      int ret = dfs(next_nums[i], left_steps - 1, visited);
      method_cnt += ret;
    }
    visited[cur_num] = false;
    return method_cnt;
  }
  void dfs2(int m, int n, int cur_num, int steps, vector<bool>& visited, int& method_cnt) {
    if(steps > n) {
      return;
    }
    if(steps >= m) {
      method_cnt++;
    }
    visited[cur_num] = true;
    vector<int> next_nums = findNextNum(cur_num, visited);
    for (int i = 0; i < next_nums.size(); i++) {
      dfs2(m, n, next_nums[i], steps+1, visited, method_cnt);
    }
    visited[cur_num] = false; 
  }
  int numberOfPatterns2(int m, int n) {
    int total_cnt = 0;
    vector<bool> visited(10, false);
    int method_cnt = 0;
    dfs2(m, n, 1, 1, visited, method_cnt);
    total_cnt +=method_cnt*4;
    method_cnt = 0;
    dfs2(m, n, 2, 1, visited, method_cnt);
    total_cnt +=method_cnt*4;
    method_cnt = 0;
    dfs2(m, n, 5, 1, visited, method_cnt);
    total_cnt += method_cnt;
    return total_cnt;
  }

  int numberOfPatterns(int m, int n) {
    int total_cnt = 0;
    vector<bool> visited(10, false);
    for (int k = m; k <= n; k++) {
      for (int i = 1; i <= 9; i++) {
        // visited.resize(10, false);
        total_cnt += dfs(i, k - 1, visited);
      }
    }
    return total_cnt;
  }
  
};

class Solution2 {
 private:
   vector<bool> used = vector<bool>(9, false);

 public:
  int numberOfPatterns(int m, int n) {
    int res = 0;
    for (int len = m; len <= n; len++) {
      res += calcPatterns(-1, len);
    }
    return res;
  }

  bool isValid(int index, int last) {
    if (used[index]) return false;
    // first digit of the pattern
    if (last == -1) return true;
    // knight moves or adjacent cells (in a row or in a column)
    if ((index + last) % 2 == 1) return true;
    // indexes are at both end of the diagonals for example 0,0, and 8,8
    int mid = (index + last) / 2;
    if (mid == 4) return used[mid];
    // adjacent cells on diagonal  - for example 0,0 and 1,0 or 2,0 and //1,1
    if ((index % 3 != last % 3) && (index / 3 != last / 3)) {
      return true;
    }
    // all other cells which are not adjacent
    return used[mid];
  }

  int calcPatterns(int last, int len) {
    if (len == 0) return 1;
    int sum = 0;
//    if(last >=0) {
//      used[last] = true;
//    }
    for (int i = 0; i < 9; i++) {
      if (isValid(i, last)) {
        used[i] = true;
        sum += calcPatterns(i, len - 1);
        used[i] = false;
      }
    }
//    if(last >=0) {
//      used[last] = false;
//    }
    return sum;
  }
};

int main(int argc, char* argv[]) {
  int m = 4, n = 4;
  Solution sol;
  cout << sol.numberOfPatterns(m, n) << endl;
  return 0;
}
