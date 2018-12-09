class Solution {
 public:
  int hIndex(vector<int>& citations) {
    if (citations.empty()) {
      return 0;
    }
    const int n = citations.size();
    vector<int> paper_cnt(n + 1, 0);
    for (int i = 0; i < n; i++) {
      if (citations[i] >= n) {
        paper_cnt[n]++;
      } else {
        paper_cnt[citations[i]]++;
      }
    }
    int paper_sum = 0;
    for (int i = n; i >= 0; i--) {
      paper_sum += paper_cnt[i];
      if (n - paper_sum <= n - i) { // paper_sum >= i
        return i;
      }
    }
  }
};
