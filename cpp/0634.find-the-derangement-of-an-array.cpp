#include <iostream>
#include <vector>

using namespace std;

// TLE.
class Solution1 {
 public:
  long dfs(int n, vector<long>& memo) {
    if (memo[n] != -1) {
      return memo[n];
    }
    int k = 2;
    while (k < n) {
      long cur = 1;
      for (int i = 2; i <= k; i++) {
        cur = (cur + dfs(i - 1, memo)) * (i);
        cur = cur % (long((1e9) + 7));
      }
      k++;
      memo[k] = cur;
    }
    return memo[k];
  }
  int findDerangement(int n) {
    vector<long> memo(n + 1, -1);
    memo[1] = 0;
    memo[2] = 1;
    long res = dfs(n, memo);
    // cout << "res: " << res << endl;
    res = res % (long(1e9 + 7));
    // cout << "res: " << res << endl;
    return ((int)res);
  }
};

class Solution {
 public:
  int findDerangement(int n) {
    vector<long> derange(n + 1, -1);
    vector<long> only_one_same(n + 1, -1);
    derange[1] = 0;
    derange[2] = 1;
    only_one_same[1] = 1;
    only_one_same[2] = 0;
    int k = 3;
    while (k <= n) {
      derange[k] = (k - 1) * derange[k - 1] + only_one_same[k - 1];
      only_one_same[k] = k * derange[k - 1];
      derange[k] %= (long((1e9l) + 7l));
      only_one_same[k] %= (long((1e9l) + 7l));
      k++;
    }
    //cout << "derange " << derange[n] << endl;
    return ((int)derange[n]);
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  //cout << sol.findDerangement(3) << endl;
  // cout << sol.findDerangement(23) << endl;
  cout << sol.findDerangement(23233) << endl;

  return 0;
}
