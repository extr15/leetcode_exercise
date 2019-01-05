class Solution {
 public:
  vector<int> findDuplicates(vector<int>& a) {
    const int n = a.size();
    vector<int> res;
    for (int i = 0; i < n; i++) {
      int idx = abs(a[i]) - 1;
      if (a[idx] > 0) {
        a[idx] *= -1;
      } else {
        res.push_back(idx + 1);
      }
    }
    return res;
  }
};

