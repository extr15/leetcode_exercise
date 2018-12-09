class Solution {
 public:
  int shortestDistance(vector<string>& words, string word1, string word2) {
    int min_dist = std::numeric_limits<int>::max();
    int idx1 = -1, idx2 = -1;
    for (int i = 0; i < words.size(); i++) {
      const string& cur = words[i];
      if (!word1.compare(cur)) {
        idx1 = i;
        if (idx2 >= 0) {
          int cur_dist = i - idx2;
          min_dist = std::min(min_dist, cur_dist);
        }
      } else if (!word2.compare(cur)) {
        idx2 = i;
        if (idx1 >= 0) {
          int cur_dist = i - idx1;
          min_dist = std::min(min_dist, cur_dist);
        }
      }
    }
    return min_dist;
  }
};
