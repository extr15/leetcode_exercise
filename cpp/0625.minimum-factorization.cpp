#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Wrong. not finish.
class Solution1 {
 public:
  void dfs(int a, int start, vector<vector<int>>& factor, int factor_idx, int& max_val) {
    if (a == 1) {
      return;
    }
    int sqrt_a = sqrt(a);
    vector<vector<int>> next = factor;
    if (a <= 9) {
      for (int i = factor_idx; i < factor.size(); i++) {
        next.push_back(factor[i]);
      }
      for (int i = factor_idx; i < factor.size(); i++) {
        next[i].push_back(a);
      }
    }
    for (int i = start; i <= min(sqrt_a, 9); i++) {
      if (a % i == 0) {
        dfs(a / i, i, next, factor.size(), max_val);
      }
    }
  }
  int smallestFactorization(int a) {
    int sqrt_a = sqrt(a);
    int max_val = 0;
    for (int i = 2; i <= min(sqrt_a, 9); i++) {
      if (a % i == 0) {
      }
    }
  }
};

// Wrong Answer, can not handle large number.
class Solution2 {
 public:
  void dfs(int a, int start, vector<vector<int>>& factor) {
    if (a == 1) {
      return;
    }
    if (a <= 9) {
      vector<int> v;
      v.push_back(a);
      factor.push_back(v);
      return;
    }
    int sqrt_a = sqrt(a);
    for (int i = start; i <= min(sqrt_a, 9); i++) {
      if (a % i == 0) {
        vector<vector<int>> tmp;
        dfs(a / i, i, tmp);
        for (auto& v : tmp) {
          v.push_back(i);
          factor.push_back(v);
        }
      }
    }
    // a must larger than 9.
    //    vector<int> v;
    //    v.push_back(a);
    //    factor.push_back(v);
  }
  int smallestFactorization(int a) {
    if (a <= 9) {
      return a;
    }
    vector<vector<int>> factor;
    dfs(a, 2, factor);
    if (factor.empty()) {
      return 0;
    }
    int min_val = std::numeric_limits<int>::max();
    bool set_min = false;
    for (auto& v : factor) {
      int val = 0;
      for (auto it = v.crbegin(); it != v.crend(); it++) {
        val = val * 10 + (*it);
      }
      if (val > 0) {
        set_min = true;
        min_val = min(min_val, val);
      }
    }
    if (set_min) {
      return min_val;
    } else {
      return 0;
    }
  }
};

// AC.
class Solution {
 public:
  void dfs(int a, int start, vector<vector<int>>& factor) {
    if (a == 1) {
      return;
    }
    if (a <= 9) {
      vector<int> v;
      v.push_back(a);
      factor.push_back(v);
      return;
    }
    int sqrt_a = sqrt(a);
    for (int i = start; i <= min(sqrt_a, 9); i++) {
      if (a % i == 0) {
        vector<vector<int>> tmp;
        dfs(a / i, i, tmp);
        for (auto& v : tmp) {
          v.push_back(i);
          factor.push_back(v);
        }
      }
    }
    // a must larger than 9.
    //    vector<int> v;
    //    v.push_back(a);
    //    factor.push_back(v);
  }
  int smallestFactorization(int a) {
    if (a <= 9) {
      return a;
    }
    vector<vector<int>> factor;
    dfs(a, 2, factor);
    if (factor.empty()) {
      return 0;
    }
    int min_val = std::numeric_limits<int>::max();
    bool set_min = false;
    const long MaxInt = std::numeric_limits<int>::max();
    for (auto& v : factor) {
      long val = 0;
      for (auto it = v.crbegin(); it != v.crend(); it++) {
        val = val * 10 + (*it);
        if (val > MaxInt) {
          break;
        }
      }
      if (val <= MaxInt) {
        set_min = true;
        min_val = min(min_val, (int)val);
      }
    }
    if (set_min) {
      return min_val;
    } else {
      return 0;
    }
  }
};

int main(int argc, char* argv[]) {
  cout << "long long max: " << std::numeric_limits<long long>::max() << endl;
  cout << "long max: " << std::numeric_limits<long>::max() << endl;
  cout << "int max: " << std::numeric_limits<int>::max() << endl;

  Solution sol;
  //int a = 10000;
  int a = 100000;
  cout << sol.smallestFactorization(a) << endl;
  return 0;
}
