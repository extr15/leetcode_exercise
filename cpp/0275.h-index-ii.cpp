class Solution {
 public:
  int hIndex(vector<int>& citations) {
    const int n = citations.size();
    if (n == 0) {
      return 0;
    }
    int left = 0, right = std::min(n, citations[n - 1]);
    while (left < right) {
      int mid = (left + right+1) / 2;
      if (citations[n-mid] >  mid) {
        left = mid;
      } else if (citations[n-mid] <  mid) {
        right = mid - 1;
      } else {
        return mid;
      }
    }
    return left;
  }
};

