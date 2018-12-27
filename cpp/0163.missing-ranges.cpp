class Solution {
 public:
  string rangeToString(int lo, int up) {
    string str = std::to_string(lo);
    if (lo < up) {
      str += ("->" + std::to_string(up));
    }
    return str;
  }
  vector<string> findMissingRanges(vector<int>& a, int lower, int upper) {
    vector<string> res;
    if (a.empty()) {
      res.push_back(rangeToString(lower, upper));
      return res;
    }
    int i = 0;
    while (a[i] < lower) {
      i++;
    }
    if (a[i] > lower) {
      res.push_back(rangeToString(lower, a[i] - 1));
    }
    while (i < a.size() - 1) {
      if (a[i] != a[i+1] && a[i] + 1 != a[i + 1]) {
        res.push_back(rangeToString(a[i] + 1, a[i + 1] - 1));
      }
      i++;
    }
    if (a[i] < upper) {
      res.push_back(rangeToString(a[i] + 1, upper));
    }
    return res;
  }
};
