#include <iostream>
#include <vector>
using namespace std;

// Wrong understanding.
class Solution2 {
 public:
  int checkLineEquation(int a, int b, int c, int d, int x, int y) {
    int ans = (d - b) * x + (a - c) * y + b * c - a * d;
    if (ans > 0) {
      ans = 1;
    } else if (ans < 0) {
      ans = -1;
    }
    return ans;
  }
  bool checkSide(const vector<vector<int>>& points, int i, int j) {
    const int a = points[i][0];
    const int b = points[i][1];
    const int c = points[j][0];
    const int d = points[j][1];
    bool prev_set = false;
    int prev;
    for (int k = i + 1; k < j; k++) {
      int cur = checkLineEquation(a, b, c, d, points[k][0], points[k][1]);
      if (!prev_set) {
        if (cur == 0) {
          continue;
        }
        prev = cur;
        prev_set = true;
      } else if (cur == 0) {
        prev = 0;
      } else if (prev != cur) {
        return false;
      }
    }
    if (prev_set && prev == 0) {
      prev_set = false;
    }
    const int n = points.size();
    for (int k = j + 1; k < n; k++) {
      int cur = checkLineEquation(a, b, c, d, points[k][0], points[k][1]);
      if (!prev_set) {
        prev = -cur;
        prev_set = true;
      } else if (cur == 0) {
        prev = 0;
      } else if (prev != -cur) {
        return false;
      }
    }
    return true;
  }
  bool isConvex(vector<vector<int>>& points) {
    const int n = points.size();
    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        if (!checkSide(points, i, j)) {
          return false;
        }
      }
    }
    return true;
  }
};

// TLE.
class Solution {
 public:
  int checkLineEquation(int a, int b, int c, int d, int x, int y) {
    int ans = (d - b) * x + (a - c) * y + b * c - a * d;
    if (ans > 0) {
      ans = 1;
    } else if (ans < 0) {
      ans = -1;
    }
    return ans;
  }
  bool checkSide(const vector<vector<int>>& points, int i, int j) {
    const int a = points[i][0];
    const int b = points[i][1];
    const int c = points[j][0];
    const int d = points[j][1];
    bool prev_set = false;
    int prev;
    const int n = points.size();
    if (j == 0) {
      j = n;
    }
    for (int p = j + 1; p < n + i; p++) {
      int k = p % n;
      int cur = checkLineEquation(a, b, c, d, points[k][0], points[k][1]);
      if (!prev_set) {
        if (cur == 0) {
          continue;
        }
        prev = cur;
        prev_set = true;
      } else if (cur == 0) {
        prev = 0;
      } else if (prev != cur) {
        // cout << "prev: " << prev << ", cur: " << cur << endl;
        return false;
      }
    }
    return true;
  }
  bool isConvex(vector<vector<int>>& points) {
    const int n = points.size();
    if (n < 3) {
      return false;
    }
    for (int i = 0; i < n; i++) {
      int j = (i + 1) % n;
      // cout << "i: " << i << ", j: " << j << endl;
      if (!checkSide(points, i, j)) {
        return false;
      }
    }
    return true;
  }
};

// AC.
class Solution {
 public:
  bool isConvex(vector<vector<int>>& points) {
    const int n = points.size();
    if (n < 3) {
      return false;
    }
    bool sign_set = false;
    int last_sign;
    for (int i = 0; i < n; i++) {
      int j = (i + 1) % n;
      int k = (i + 2) % n;
      auto& p0 = points[i];
      auto& p1 = points[j];
      auto& p2 = points[k];
      int p01_x = p1[0] - p0[0];
      int p01_y = p1[1] - p0[1];
      int p02_x = p2[0] - p0[0];
      int p02_y = p2[1] - p0[1];
      int det = p01_x * p02_y - p01_y * p02_x;
      if (det == 0) {
        continue;
      }
      if (!sign_set) {
        if (det > 0) {
          last_sign = 1;
          sign_set = true;
        } else if (det < 0) {
          last_sign = -1;
          sign_set = true;
        }
      } else {
        if (det > 0 && last_sign < 0) {
          return false;
        } else if (det < 0 && last_sign > 0) {
          return false;
        }
      }
    }
    return true;
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  vector<vector<int>> points{{0, 0}, {1, 0}, {1, 1}, {-1, 1}, {-1, 0}};
  cout << sol.isConvex(points) << endl;

  return 0;
}
