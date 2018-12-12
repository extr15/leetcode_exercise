class Solution {
 public:
  void wiggleSort(vector<int>& a) {
    const int n = a.size();
    if (n < 2) {
      return;
    }
    bool should_up = true;
    for (int i = 1; i < n; i++) {
      if ((should_up && a[i] < a[i - 1]) || (!should_up && a[i] > a[i - 1])) {
        std::swap(a[i], a[i - 1]);
      }
      should_up = !should_up;
    }
  }
};
