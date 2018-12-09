class WordDistance {
 public:
  WordDistance(vector<string> words) {
    for (int i = 0; i < words.size(); i++) {
      const string& cur_word = words[i];
      if (word_idx.find(cur_word) != word_idx.end()) {
        word_idx[cur_word].push_back(i);
      } else {
        vector<int> idx;
        idx.push_back(i);
        word_idx.insert({cur_word, idx});
      }
    }
  }

  int shortest(string word1, string word2) {
    const vector<int>& idx1 = word_idx[word1];
    const vector<int>& idx2 = word_idx[word2];
    int min_dist = std::numeric_limits<int>::max();
    int i = 0, j = 0;
    while (i < idx1.size() && j < idx2.size()) {
      int cur_dist = std::abs(idx1[i] - idx2[j]);
      min_dist = std::min(min_dist, cur_dist);
      if (idx1[i] > idx2[j]) {
        j++;
      } else {
        i++;
      }
    }
    return min_dist;
  }

 private:
  map<string, vector<int>> word_idx;
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance obj = new WordDistance(words);
 * int param_1 = obj.shortest(word1,word2);
 */
