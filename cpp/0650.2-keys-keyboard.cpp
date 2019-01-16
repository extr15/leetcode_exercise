// Wrong. dp.
class Solution {
 public:
  int minSteps(int n) {
    int k = ;
    vector<int> cnt(n + 1);
    vector<int> paste(n + 1);
    cnt[0] = 1;
    paste[0] = 0;
    cnt[1] = 1;
    paste[1] = 1;
    //      cnt[2] = 2;
    //      paste[2] = 1;

    for (int k = 2; k <= n; k++) {
      cnt[k] = paste[k - 1] * 2;
      cnt[k] = max(cnt[k], cnt[k - 2] * 2);
      if (cnt[k] == n) {
        return k;
      }
      paste[k] = cnt[k - 2];
    }
    return n;
  }
};

// Wrong, n=6; or n=2^8*7*13;
class Solution {
 public:
  int minSteps(int n) {
    const int sqrt_n = sqrt(n);
    int cnt = 0;
    for (int i = 2; i < sqrt_n;) {
      if (n == 1) {
        break;
      }
      if (n % i == 0) {
        n = n / i;
        cnt += i;
      } else {
        i++;
      }
    }
    if (n > 1) {
      return n;
    } else {
      return cnt;
    }
  }
};

// AC.
class Solution {
 public:
  int minSteps(int n) {
    int cnt = 0;
    for (int i = 2; i <= n;) {
      if (n == 1) {
        break;
      }
      if (n % i == 0) {
        n = n / i;
        cnt += i;
      } else {
        i++;
      }
    }
    return cnt;
  }
};
