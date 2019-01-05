class Solution {
 public:
  vector<int> findDisappearedNumbers(vector<int>& a) {
    const int n = a.size();
    for (int i = 0; i < n; i++) {
      while (a[a[i] - 1] != a[i]) {
        swap(a[a[i] - 1], a[i]);
      }
    }
    vector<int> res;
    for (int i = 0; i < n; i++) {
      if (a[i] != i + 1) {
        res.push_back(i + 1);
      }
    }
    return res;
  }
};

class Solution {
 public:
  vector<int> findDisappearedNumbers(vector<int>& a) {
    const int n = a.size();
    for (int i = 0; i < n; i++) {
      int idx = std::abs(a[i]) - 1;
      if (a[idx] > 0) {
        a[idx] *= -1;
      }
    }
    vector<int> res;
    for (int i = 0; i < n; i++) {
      if (a[i] > 0) {
        res.push_back(i + 1);
      }
    }
    return res;
  }
};
