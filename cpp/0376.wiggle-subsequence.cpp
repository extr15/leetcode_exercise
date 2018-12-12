class Solution {
 public:
  int wiggleMaxLength(vector<int>& a) {
    const int n = a.size();
    if (n <= 1) {
      return n;
    }

    int cur_wiggle_len = 1;
    bool is_positive = (a[1] > a[0]);
    bool is_init = true;
    for (int i = 1; i < n; i++) {
      if (a[i] == a[i - 1]) {
        continue;
      }
      if (is_init) {
        is_positive = (a[i] > a[i - 1]);
        is_init = false;
        cur_wiggle_len = 2;
        continue;
      }

      bool is_wiggle = false;
      if (is_positive && a[i] < a[i - 1]) {
        is_wiggle = true;
      }
      if (!is_positive && a[i] > a[i - 1]) {
        is_wiggle = true;
      }
      if (is_wiggle) {
        cur_wiggle_len++;
        is_positive = !is_positive;
      }
    }
    return cur_wiggle_len;
  }
};
