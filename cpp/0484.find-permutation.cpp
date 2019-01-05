// Wrong.
class Solution {
 public:
  vector<int> findPermutation(string s) {
    vector<int> res;
    if (s.empty()) {
      return res;
    }
    const int len = s.size();
    const int n = len + 1;
    int min_val = 1;
    int cur = 1;
    res.push_back(cur);
    int next_pos = 2;
    int next_neg = 0;
    for (int i = 0; i < len; i++) {
      if (s[i] == 'I') {
        res.push_back(next_pos);
        next_pos++;
      } else {
        min_val = next_neg;
        res.push_back(next_neg);
        next_neg--;
      }
    }
    if (min_val < 1) {
      int delta = 1 - min_val;
      for (int i = 0; i < n; i++) {
        res[i] += delta;
      }
    }
    return res;
  }
};

// AC.
class Solution {
 public:
  vector<int> findPermutation(string s) {
    vector<int> res;
    if (s.empty()) {
      return res;
    }
    const int len = s.size();
    const int n = len + 1;
    res.resize(n);
    int cur = n;
    int i = len - 1;
    while (i >= 0) {
      if (s[i] == 'I') {
        res[i + 1] = cur;
        cur--;
      } else {
        int k = i;
        while (i >= 0 && s[i] == 'D') {
          i--;
        }
        for (int j = i; j <= k; j++) {
          res[j + 1] = cur;
          cur--;
        }
      }
      i--;
    }
    if (s[0] == 'I') {
      res[0] = 1;
    }
    return res;
  }
};

