class Solution {
 public:
  int maxDistance(vector<vector<int>>& arrays) {
    const int n = arrays.size();
    //      vector<int> min_val(n, std::numeric_limits<int>::max());
    //      vector<int> max_val(n, std::numeric_limits<int>::min());
    vector<int> min_val(n);
    vector<int> max_val(n);
    for (int i = 0; i < n; i++) {
      auto& a = arrays[i];
      int cur_min = a[0], cur_max = a[0];
      for (auto v : a) {
        cur_min = min(cur_min, v);
        cur_max = max(cur_max, v);
      }
      min_val[i] = cur_min;
      max_val[i] = cur_max;
    }
    int first_min, second_min, first_max, second_max;
    first_min = second_min = std::numeric_limits<int>::max();
    first_max = second_max = std::numeric_limits<int>::min();
    int first_min_idx = -1, first_max_idx = -1;
    for (int i = 0; i < n; i++) {
      int cur_min = min_val[i];
      int cur_max = max_val[i];
      if (cur_min < first_min) {
        second_min = first_min;
        first_min = cur_min;
        first_min_idx = i;
      } else if (cur_min < second_min) {
        second_min = cur_min;
      }
      if (cur_max > first_max) {
        second_max = first_max;
        first_max = cur_max;
        first_max_idx = i;
      } else if (cur_max > second_max) {
        second_max = cur_max;
      }
    }
    if (first_min_idx != first_max_idx) {
      return first_max - first_min;
    } else {
      int d1 = second_max - first_min;
      int d2 = first_max - second_min;
      if (d1 > d2) {
        return d1;
      } else {
        return d2;
      }
    }
  }
};
