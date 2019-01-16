class Solution {
 public:
  string findContestMatch(int n) {
    vector<string> cur(n);
    for (int i = 1; i <= n; i++) {
      cur[i - 1] = std::to_string(i);
    }
    while (n > 1) {
      int half_n = n / 2;
      vector<string> next;
      next.reserve(half_n);
      for (int i = 0; i < half_n; i++) {
        next.emplace_back("(" + cur[i] + "," + cur[n - 1 - i] + ")");
      }
      std::swap(cur, next);
      n = half_n;
    }
    return cur[0];
  }
};
