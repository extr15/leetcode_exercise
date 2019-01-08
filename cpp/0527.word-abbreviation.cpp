class Solution {
 public:
  void findAbbr(const vector<string>& words, unordered_map<string, string>& str_to_abbr) {
    // unordered_map<prefix, vector<pair<str, prefix_len> >
    unordered_map<string, vector<pair<string, int>>> prefix_to_word;
    const int len = words[0].size();
    for (auto& w : words) {
      string prefix = w.substr(len - 1, 1) + w.substr(0, 1);
      prefix_to_word[prefix].push_back({w, 1});
    }
    while (!prefix_to_word.empty()) {
      unordered_map<string, vector<pair<string, int>>> next_prefix_to_word;
      for (auto it = prefix_to_word.begin(); it != prefix_to_word.end(); it++) {
        string prefix = it->first;
        auto str_and_prefix_idx = it->second;
        if (str_and_prefix_idx.size() == 1 || prefix.length() == len - 1) {
          for (auto& cur : str_and_prefix_idx) {
            string& cur_word = cur.first;
            int prefix_len = cur.second;
            string abbr;
            if (len - prefix_len - 1 > 1) {
              abbr = prefix.substr(1, prefix_len) + std::to_string(len - prefix_len - 1) +
                     cur_word[len - 1];
            } else {
              abbr = cur_word;
            }
            str_to_abbr.insert({cur_word, abbr});
          }
        } else {
          for (auto& cur : str_and_prefix_idx) {
            string& cur_word = cur.first;
            int prefix_len = cur.second;
            string next_prefix = prefix + cur_word[prefix_len];
            next_prefix_to_word[next_prefix].push_back({cur_word, prefix_len + 1});
          }
        }
      }
      std::swap(prefix_to_word, next_prefix_to_word);
    }
  }
  vector<string> wordsAbbreviation(vector<string>& dict) {
    unordered_map<int, vector<string>> len_to_str;
    for (auto& s : dict) {
      len_to_str[s.size()].push_back(s);
    }
    vector<string> res;
    unordered_map<string, string> str_to_abbr;
    for (auto& s : len_to_str) {
      findAbbr(s.second, str_to_abbr);
    }
    for (auto& s : dict) {
      res.push_back(str_to_abbr[s]);
    }
    return res;
  }
};

