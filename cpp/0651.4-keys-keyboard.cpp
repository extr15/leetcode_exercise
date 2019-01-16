#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Wrong.
class Solution1 {
 public:
  int maxA_Wrong(int N) {
    vector<int> cnt(N + 1, 0);
    vector<int> paste(N + 1, 0);
    cnt[0] = 0;
    cnt[1] = 1;
    cnt[2] = 2;
    cnt[3] = 3;
    paste[0] = 0;
    paste[1] = 0;
    paste[2] = 0;
    paste[3] = 1;
    paste[4] = 2;
    for (int i = 4; i <= N; i++) {
      int cnt_by_paste_last = cnt[i - 1] + paste[i - 1];
      // int cnt_by_paste_last = 2* paste[i - 1];
      int cnt_by_input_A = cnt[i - 1] + 1;
      int cnt_by_copy_and_paste = 2 * cnt[i - 3];
      cnt[i] = max(cnt_by_paste_last, cnt_by_input_A);
      cnt[i] = max(cnt[i], cnt_by_copy_and_paste);

      // paste[i] = max(2 * cnt[i - 2], paste[i - 1]);
      paste[i] = max(cnt[i - 2], paste[i - 1]);
      cout << "i: " << i << ", cnt[i]: " << cnt[i] << ", paste[i]: " << paste[i] << endl;
    }
    return cnt[N];
  }
  int maxA(int N) {
    // 0: `A`, 1: `ctrl+A`, 2: `ctrl+C`, 3: `ctrl+V`, 4: max cnt.
    vector<vector<int>> dp(N + 1, vector<int>(5, 0));
    dp[1][0] = 1;
    dp[1][1] = 0;
    dp[1][2] = 0;
    dp[1][3] = 0;
    dp[1][4] = 1;
    for (int i = 4; i <= N; i++) {
      dp[i][0] = dp[i - 1][4] + 1;
      dp[i][1] = dp[i - 1][4];
      dp[i][2] = dp[i - 1][1];
      dp[i][3] = dp[i - 1][2] * 2;
      dp[i][4] = max(dp[i][0], dp[i][1]);
      dp[i][4] = max(dp[i][4], dp[i][2]);
      dp[i][4] = max(dp[i][4], dp[i][3]);
    }
    return dp[N][4];

    vector<int> cnt(N + 1, 0);
    vector<int> paste(N + 1, 0);
    cnt[0] = 0;
    cnt[1] = 1;
    cnt[2] = 2;
    cnt[3] = 3;
    paste[0] = 0;
    paste[1] = 0;
    paste[2] = 0;
    paste[3] = 1;
    paste[4] = 2;
    for (int i = 4; i <= N; i++) {
      int cnt_by_paste_last = cnt[i - 1] + paste[i - 1];
      // int cnt_by_paste_last = 2* paste[i - 1];
      int cnt_by_input_A = cnt[i - 1] + 1;
      int cnt_by_copy_and_paste = 2 * cnt[i - 3];
      cnt[i] = max(cnt_by_paste_last, cnt_by_input_A);
      cnt[i] = max(cnt[i], cnt_by_copy_and_paste);

      // paste[i] = max(2 * cnt[i - 2], paste[i - 1]);
      paste[i] = max(cnt[i - 2], paste[i - 1]);
      cout << "i: " << i << ", cnt[i]: " << cnt[i] << ", paste[i]: " << paste[i] << endl;
    }
    return cnt[N];
  }
};

class Solution {
 public:
   // TLE.
  void dfs(int step, int n, int cnt, int paste, bool select_all, int& max_cnt) {
    if (step == n) {
      max_cnt = max(max_cnt, cnt);
      return;
    }
    // press select all.
    dfs(step + 1, n, cnt, paste, true, max_cnt);
    if (select_all) {
      // press copy
      dfs(step + 1, n, cnt, cnt, false, max_cnt);
    }
    // press paste
    dfs(step + 1, n, cnt + paste, paste, false, max_cnt);
    // press A
    dfs(step + 1, n, cnt + 1, paste, false, max_cnt);
  }
  inline long getId(int cnt, int paste) {
    return (long)(((long)cnt<<32) + paste);
  }
  // AC.
  void dfs2(int step, int n, int cnt, int paste, int& max_cnt, unordered_map<long, int>& cache) {
    if(step > n) {
      return;
    }
    if (step == n) {
      max_cnt = max(max_cnt, cnt);
      return;
    }
    long id = getId(cnt, paste);
    if(cache.find(id) != cache.end() && cache[id] <= step) {
      return;
    }
    if(paste > 1) {
      dfs2(step+1, n, cnt+paste, paste, max_cnt, cache);
    }
    else {
      dfs2(step+1, n, cnt+1, paste, max_cnt, cache);
    }
    dfs2(step+3, n, cnt*2, cnt, max_cnt, cache);
    cache[id] = step;
  }
  int maxA(int n) {
    int max_cnt = -1;
    //dfs(0, n, 0, 0, false, max_cnt);
    unordered_map<long, int> cache;
    dfs2(0, n, 0, 0, max_cnt, cache);
    return max_cnt;
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  // cout << sol.maxA(5) << endl;
  //cout << sol.maxA(7) << endl;
  //cout << sol.maxA(18) << endl;
  cout << sol.maxA(12) << endl;
  return 0;
}
