class Solution {
 public:
  int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
    const int n = flights.size();
    const int k = days[0].size();
    vector<int> dp(n, 0);  // max sum of vacation days of each city.
    vector<bool> is_city_available(n, false);
    is_city_available[0] = true;
    for (int i = 1; i < n; i++) {
      if (flights[0][i]) {
        is_city_available[i] = true;
      }
    }
    for (int j = 0; j < k; j++) {
      vector<bool> next_city_available(n, false);
      vector<int> next_dp(n, 0);
      for (int i = 0; i < n; i++) {
        if (is_city_available[i]) {
          next_city_available[i] = true;
          next_dp[i] = max(next_dp[i], dp[i] + days[i][j]);
          for (int p = 0; p < n; p++) {
            if (flights[i][p]) {
              next_city_available[p] = true;
              next_dp[p] = max(next_dp[p], dp[i] + days[p][j]);
            }
          }
        }
      }
      is_city_available = next_city_available;
      dp = next_dp;
    }
    int max_day = 0;
    for (int i = 0; i < n; i++) {
      max_day = max(max_day, dp[i]);
    }
    return max_day;
  }
};
