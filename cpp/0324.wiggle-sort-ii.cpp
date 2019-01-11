// Failed.
class Solution {
 public:
  void wiggleSort(vector<int>& a) {
    std::sort(a.begin(), a.end());
    const int n = a.size();
    const bool is_odd = (n % 2 == 1);
    int mid = n / 2;
    if (is_odd) {
      mid++;
    }
    vector<int> res;
    if (is_odd) {
      for (int i = 0; i + mid < n; i++) {
        res.push_back(a[i]);
        res.push_back(a[mid + i]);
      }
    } else {
      for (int i = 0; i + mid < n; i++) {
        res.push_back(a[mid + i]);
        res.push_back(a[i]);
      }
    }
    if (is_odd) {
      res.push_back(a[mid - 1]);
    }
    std::copy(res.begin(), res.end(), a.begin());
  }
};
