class Solution {
 public:
  int shortestWordDistance(vector<string>& words, string word1, string word2) {
    const int n = words.size();
    const bool same_word = !word1.compare(word2);
    int min_dist = std::numeric_limits<int>::max();
    if (same_word) {
      int last_idx = -1, cur_idx = -1;
      for (int i = 0; i < n; i++) {
        const string& cur_word = words[i];
        if (!word1.compare(cur_word)) {
          cur_idx = i;
          if (last_idx >= 0) {
            min_dist = std::min(min_dist, cur_idx - last_idx);
          }
          last_idx = cur_idx;
        }
      }
    } else {
      int idx1 = -1, idx2 = -1;
      for (int i = 0; i < n; i++) {
        const string& cur_word = words[i];
        if (!word1.compare(cur_word)) {
          idx1 = i;
          if (idx2 >= 0) {
            min_dist = std::min(min_dist, i - idx2);
          }
        } else if (!word2.compare(cur_word)) {
          idx2 = i;
          if (idx1 >= 0) {
            min_dist = std::min(min_dist, i - idx1);
          }
        }
      }
    }

    return min_dist;
  }
};
