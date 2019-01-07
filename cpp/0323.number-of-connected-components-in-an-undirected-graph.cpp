#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findRootIterative(vector<int>& roots, int idx) {
    while (roots[idx] != idx) {
      roots[idx] = roots[roots[idx]];
      idx = roots[idx];
    }
    return idx;
  }
  int findRoot(vector<int>& roots, int idx) {
    if (roots[idx] != idx) {
      roots[idx] = findRoot(roots, roots[idx]);
    }
    return roots[idx];
  }
  int countComponents(int n, vector<pair<int, int>>& edges) {
    if (n <= 0) {
      return 0;
    }
    vector<int> roots(n);
    vector<int> ranks(n);
    for (int i = 0; i < n; i++) {
      roots[i] = i;
    }
    for (auto& e : edges) {
      //      int root_1 = findRoot(roots, e.first);
      //      int root_2 = findRoot(roots, e.second);
      int root_1 = findRootIterative(roots, e.first);
      int root_2 = findRootIterative(roots, e.second);
      //      cout << "root: " << root_1 << ", " << root_2 << ", "
      //        << ranks[root_1] << ", " << ranks[root_2] << endl;
      if (root_1 != root_2) {
        if (ranks[root_1] > ranks[root_2]) {
          roots[root_2] = root_1;
        } else if (ranks[root_1] < ranks[root_2]) {
          roots[root_1] = root_2;
        } else {
          roots[root_2] = root_1;
          ranks[root_1]++;
        }
      }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      int root_i = findRootIterative(roots, i);
      if (root_i == i) {
        cnt++;
      }
    }
    return cnt;
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  vector<pair<int, int>> edges;
  //  edges.push_back({0, 1});
  //  edges.push_back({0, 2});
  edges.push_back({1, 0});
  edges.push_back({2, 0});
  cout << sol.countComponents(3, edges) << endl;

  return 0;
}
