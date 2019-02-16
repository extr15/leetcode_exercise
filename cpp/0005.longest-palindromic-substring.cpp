class Solution {
 public:
  string longestPalindrome(string s) {
    if (s.empty()) {
      return "";
    }
    const int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      dp[i][0] = 1;
    }
    int max_len = 0; // not 1, s="ac"
    int start_idx = 0;
    for (int len = 1; len <= n; len++) {
      for (int i = 0; i + len < n; i++) {
        if (s[i] == s[i + len] && (len==1 || dp[i + 1][len - 2] == 1) ) {
          dp[i][len] = 1;
          max_len = len;
          start_idx = i;
        }
      }
    }
    return s.substr(start_idx, max_len + 1);
  }
};
