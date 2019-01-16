#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Wrong.
class Solution1 {
 public:
  vector<int> cheapestJump(vector<int>& a, int b) {
    vector<int> res;
    const int n = a.size();
    if (n == 1) {
      res.push_back(1);
      return res;
    }
    vector<int> dp(n + 1, -1);
    vector<int> prev_idx(n + 1, 0);
    dp[1] = a[0];
    prev_idx[1] = 0;
    if (b <= 0) {
      return res;
    }
    bool can_jump = false;
    for (int i = 2; i <= min(1 + b, n); i++) {
      if (a[i - 1] >= 0) {
        dp[i] = a[0] + a[i - 1];
        prev_idx[i] = 1;
        can_jump = true;
      }
    }
    if (!can_jump) {
      return res;
    }
    if (1 + b >= n) {
      if (a[n - 1] >= 0) {
        res.push_back(1);
        // Input: [1,0,1] 2 , Expected [1,2,3]
        for (int i = 2; i < n; i++) {
          if (a[i - 1] == 0) {
            res.push_back(i);
          }
        }
        res.push_back(n);
        return res;
      } else {
        return res;
      }
    }
    for (int j = b + 2; j <= n; j++) {
      if (a[j - 1] < 0) {
        dp[j] = -1;
        continue;
      }
      int min_coin = -1;
      int prev = -1;
      for (int i = j - 1; i >= j - b; i--) {
        if (dp[i] >= 0) {
          if (min_coin < 0 || dp[i] <= min_coin) {
            min_coin = dp[i];
            prev = i;
          }
        }
      }
      if (min_coin >= 0) {
        dp[j] = min_coin + a[j - 1];
        ;
        prev_idx[j] = prev;
      }
    }
    if (dp[n] < 0) {
      return res;
    } else {
      stack<int> path;
      int prev = n;
      while (prev > 0) {
        path.push(prev);
        int cur = prev;
        prev = prev_idx[prev];
        for (int i = cur - 1; i > prev; i--) {
          if (a[i - 1] == 0) {
            path.push(i);
          }
        }
      }
      while (!path.empty()) {
        res.push_back(path.top());
        path.pop();
      }
      return res;
    }
  }
};

// AC.
class Solution {
 public:
   bool cmpPath(const vector<int>& p1, const vector<int>& p2) {
     int i=0, j=0;
     const int n1 = p1.size();
     const int n2 = p2.size();
     while(i < n1 && j < n2) {
       if(p1[i] != p2[j]) {
         return p1[i] < p2[j];
       }
       else {
         i++;
         j++;
       }
     }
     if(i != n1) {
       return true;
     }
     else {
       return false;
     }
   }
  vector<int> cheapestJump(vector<int>& a, int b) {
    vector<int> res;
    const int n = a.size();
    if (n == 1) {
      res.push_back(1);
      return res;
    }
    vector<int> dp(n + 1, -1);
    vector<vector<int>> prev_path(n + 1, vector<int>());
    dp[1] = a[0];
    prev_path[1].push_back(1);
    if (b <= 0) {
      return res;
    }
    for (int j = 2; j <= n; j++) {
      if (a[j - 1] < 0) {
        dp[j] = -1;
        continue;
      }
      int min_coin = -1;
      int prev = -1;
      for (int i = j - 1; i >= max(j - b, 1); i--) {
        if (dp[i] >= 0) {
          if (min_coin < 0 || dp[i] < min_coin || (dp[i] == min_coin && 
                cmpPath(prev_path[i], prev_path[prev]) )) {
            min_coin = dp[i];
            prev = i;
          }
        }
      }
      if (min_coin >= 0) {
        dp[j] = min_coin + a[j - 1];
        prev_path[j] = prev_path[prev];
        prev_path[j].push_back(j);
      }
    }
    if (dp[n] < 0) {
      return res;
    } else {
      return prev_path[n];
    }
  }
};

class Solution2 {
 public:
  vector<int> cheapestJump(vector<int>& a, int b) {
    vector<int> res;
    const int n = a.size();
    if (n == 1) {
      res.push_back(1);
      return res;
    }
    vector<int> dp(n + 1, -1);
    vector<int> prev_idx(n+1 , 0);
    dp[1] = a[0];
    prev_idx[1] = 0;
    if (b <= 0) {
      return res;
    }
    for(int i=1; i<n; i++) {
      if(a[i-1] < 0 || dp[i] < 0) {
        continue;
      }
      for(int j=i+1; j<=i+b && j<n+1; j++) {
        if(dp[j] < 0 || dp[i]+a[j-1] < dp[j]) {
          dp[j] = dp[i] + a[j-1];
          prev_idx[j] = i;
        }
      }
    }
    if (dp[n] < 0) {
      return res;
    } else {
      stack<int> path;
      int prev = n;
      while(prev > 0) {
        path.push(prev);
        prev = prev_idx[prev];
      }
      while(!path.empty()) {
        res.push_back(path.top());
        path.pop();
      }
      return res;
    }
  }
};

int main(int argc, char* argv[]) {
  vector<int> a{28, 44, 71, -1, 99, 59, 78, 60, 80, 18, 71, 1,  68, 6,  19, 66, 62, 74,
                7,  67, 18, 70, 22, 15, 6,  58, 95, 26, 52, 38, 80, 60, 34, 56, 9,  8,
                34, 3,  25, 33, 45, 35, 15, 27, 97, 22, 2,  2,  71, 91, 44, 28, 91, 93,
                25, 2,  53, 54, 15, 14, 56, 97, 51, 36, 81, 29, 15, 58, 97};
  int b = 42;
  // answer should be: res: 1(28), 12(1), 47(2), 69(97). not 1(28), 38(3), 69(97).
  Solution sol;
  auto res = sol.cheapestJump(a, b);
  cout << "res: ";
  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << "(" << a[res[i]-1] << "), ";
  }
  cout << endl;

  return 0;
}
