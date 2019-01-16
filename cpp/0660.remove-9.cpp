#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// AC.
class Solution {
 public:
  typedef long Type;
  vector<Type> calcContain9Cnt(int n) {
    int digit_cnt = 1;
    int p = n;
    while (p > 10) {
      p /= 10;
      digit_cnt++;
    }
    vector<Type> dp(digit_cnt * 9 + 1, 0);
    Type last_k_cnt = 0;
    for (int k = 1; k <= digit_cnt; k++) {
      Type cur_k_cnt = last_k_cnt;
      for (int s = 1; s <= 8; s++) {
        int idx = s + (k - 1) * 9;
        dp[idx] = last_k_cnt + cur_k_cnt;
        cur_k_cnt = dp[idx];
      }
      dp[9 * k] = pow(10, k - 1) + cur_k_cnt;
      last_k_cnt = dp[9 * k];
    }
    return dp;
  }
  int getContain9CntLessThan(const vector<Type>& dp, int n) {
    if (n == 0) {
      return 0;
    }
    int digit_cnt = 1;
    int p = n;
    while (p > 10) {
      p /= 10;
      digit_cnt++;
    }
    int left = n - p * pow(10, digit_cnt - 1);
    //    cout << "n: " << n << ", p: " << p << ", digit_cnt: " << digit_cnt << ", left: " << left
    //         << endl;
    if (p != 9) {
      return dp[(p - 1) + (digit_cnt - 1) * 9] + getContain9CntLessThan(dp, left);
    } else {
      return dp[8 + (digit_cnt - 1) * 9] + left + 1;
    }
  }
  bool isContain9(int n) {
    while (n > 10) {
      int t = n % 10;
      if (t == 9) {
        return true;
      }
      n /= 10;
    }
    return n == 9;
  }
  // Wrong, when n = 5000000.
  int newInteger(int n) {
    Type lo = n;
    //Type hi = 2 * n;
    Type hi = std::numeric_limits<int>::max();
    //auto dp = calcContain9Cnt(2 * n);
    auto dp = calcContain9Cnt(hi);
    //    cout << "dp: ";
    //    for (int i = 0; i < dp.size(); i++) {
    //      cout << i << "(" << dp[i] << ") ";
    //    }
    //    cout << endl;
    while (lo < hi) {
      //int mid = (lo + hi) / 2;
      int mid = lo + (hi - lo) / 2;
      int m = getContain9CntLessThan(dp, mid);
      if (mid - m == n) {
        if (isContain9(mid)) {
          hi = mid - 1;
        } else {
          return mid;
        }
      } else if (mid - m > n) {
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    }
    return lo;
  }
  int newInteger_base9(int n) {
    int res = 0;
    int mul = 1;
    while(n > 0) {
      int t = n % 9;
      res = res + mul * t;
      mul *= 10;
      n /= 9;
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  int n = atoi(argv[1]);
  Solution sol;
   //int n = 9;
  // int n = 8;
  // int n = 2;
  // int n = 800000000;
  //int n = 10000000;
  //int n = 100;
  cout << "n: " << n << ", new: " << sol.newInteger(n) << endl;
  cout << "base 9 n: " << n << ", new: " << sol.newInteger_base9(n) << endl;

  return 0;
}

//800000000
//2052305618
// 1225159022
