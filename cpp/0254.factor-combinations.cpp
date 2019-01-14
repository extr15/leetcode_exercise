#include <iostream>
#include <vector>

using namespace std;

void output2dVec(const vector<vector<int>>& v) {
  cout << "[";
  for (auto v1 : v) {
    cout << "[ ";
    for (auto v2 : v1) {
      cout << v2 << " ";
    }
    cout << "]";
  }
  cout << "]" << endl;
}

// AC.
class Solution {
 public:
  vector<vector<int>> calcFactors(int n, int start) {
    vector<vector<int>> res;
    for (int i = start; i < n; i++) {
      if (n % i != 0) {
        continue;
      }
      vector<vector<int>> tmp = calcFactors(n / i, i);
      // cout << "i: " << i << endl;
      // output2dVec(tmp);
      for (auto& v : tmp) {
        v.push_back(i);
      }
      std::copy(tmp.begin(), tmp.end(), std::back_inserter(res));
    }
    if (n >= start) {
      vector<int> v;
      v.push_back(n);
      res.push_back(v);
    }
    // cout << "res: " << endl;
    // output2dVec(res);
    return res;
  }

  vector<vector<int>> getFactors(int n) {
    vector<vector<int>> res;
    res = calcFactors(n, 2);
    for (auto it = res.begin(); it != res.end();) {
      if (it->size() == 1) {
        it = res.erase(it);
      } else {
        it++;
      }
    }
    return res;
  }
};

class Solution {
 public:
  void dfs(int n, int start, vector<int>& path, vector<vector<int>>& res) {
    if (n == 1) {
      // handle original n is `1`.
      if (!path.empty()) {
        res.push_back(path);
      }
      return;
    }
    if (start > n) {
      return;
    }
    const int sqrt_n = sqrt(n);
    for (int i = start; i <= sqrt_n; i++) {
      if (n % i == 0) {
        path.push_back(i);
        dfs(n / i, i, path, res);
        path.pop_back();
      }
    }
    // original n=37, should return [], instead of [[37]].
    if (!path.empty()) {
      path.push_back(n);
      res.push_back(path);
      // Don't forget to pop_back.
      path.pop_back();
    }
  }
  vector<vector<int>> getFactors(int n) {
    vector<vector<int>> res;
    vector<int> path;
    dfs(n, 2, path, res);
    return res;
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  auto res = sol.getFactors(12);
  output2dVec(res);

  return 0;
}
