#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
//#define Debug(x) x
#define Debug(x) 
 public:
  string minWindow(string S, string T) {
    if (S.empty() || T.empty()) {
      return "";
    }
    const int m = S.size();
    const int n = T.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    {
      int start = -1;
      for (int i = 0; i < m; i++) {
        if (S[i] == T[0]) {
          start = i;
        }
        dp[0][i] = start;
      }
    }
    for (int j = 1; j < n; j++) {
      Debug(cout << "--- j: " << j << endl);
      int start_idx = -1;
      for (int i = 1; i < m; i++) {
        if (S[i] == T[j]) {
          if (dp[j - 1][i - 1] >= 0) {
            dp[j][i] = dp[j - 1][i - 1];
            start_idx = dp[j - 1][i - 1];
          } else {
            dp[j][i] = -1;
          }
          Debug(cout << "i: " << i << ", dp[j - 1][i - 1]: " << dp[j - 1][i - 1] << ", dp[j][i]: " << dp[j][i] << endl);
        } else {
          dp[j][i] = start_idx;  // Not: dp[j - 1][i];
        }
      }
    }
    int max_len = m + 1;
    string res;
    for (int i = 0; i < m; i++) {
       Debug(cout << "i: " << i << ", " << dp[n - 1][i] << endl);
      if (dp[n - 1][i] >= 0) {
        int len = i - dp[n - 1][i] + 1;
        if (len < max_len) {
          res = S.substr(dp[n - 1][i], len);
          max_len = len;
        }
      }
    }
    return res;
  }
};

int main(int argc, char *argv[]) {
  Solution sol;
  //string S = "abcdebdde", T = "bde";
  string S = "fgrqsqsnodwmxzkzxwqegkndaa", T = "fnok";
  string res = sol.minWindow(S, T);
  cout << "res: " << res << endl;

  return 0;
}
