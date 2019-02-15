#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Solution {
 public:
  bool dfs(const vector<int>& a, int i, bool is_odd, vector<int>& can_reach_odd,
           vector<int>& can_reach_even) {
    const int n = a.size();
    if (i == n - 1) {
      return true;
    }
    if (is_odd) {
      if (can_reach_odd[i] != -1) {
        return can_reach_odd[i];
      }
      int min_j = -1;
      int cur_min = std::numeric_limits<int>::max();
      for (int j = i + 1; j < n; j++) {
        if (a[j] < a[i]) {
          continue;
        }
        if (a[j] < cur_min) {
          cur_min = a[j];
          min_j = j;
        }
      }
      if (min_j > 0) {
        can_reach_odd[i] = dfs(a, min_j, false, can_reach_odd, can_reach_even);
      } else {
        can_reach_odd[i] = false;
      }
      return can_reach_odd[i];
    } else {
      if (can_reach_even[i] != -1) {
        return can_reach_even[i];
      }
      int cur_max = std::numeric_limits<int>::min();
      int max_j = -1;
      for (int j = i + 1; j < n; j++) {
        if (a[j] > a[i]) {
          continue;
        }
        if (a[j] > cur_max) {
          cur_max = a[j];
          max_j = j;
        }
      }
      if (max_j > 0) {
        can_reach_even[i] = dfs(a, max_j, true, can_reach_odd, can_reach_even);
      } else {
        can_reach_even[i] = false;
      }
      return can_reach_even[i];
    }
  }
  int oddEvenJumps(vector<int>& a) {
    const int n = a.size();
    vector<int> can_reach_odd(n, -1);
    vector<int> can_reach_even(n, -1);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      if (dfs(a, i, true, can_reach_odd, can_reach_even)) {
        cnt++;
      }
    }
    // vector<pair<bool, bool> > can_reach(n, pair<bool, bool>(false, false));
    return cnt;
  }
};

int main(int argc, char *argv[]) {
  
    return 0;
}
