class ValidWordAbbr {
 public:
  string calcAbbr(const string& s) {
    if (s.size() <= 2) {
      return s;
    }
    string res;
    res += s[0];
    const int n = s.size();
    res += (std::to_string(n - 2) + s[n - 1]);
    return res;
  }
  ValidWordAbbr(vector<string> dictionary) {
    for (auto s : dictionary) {
      if(original_string_.find(s) != original_string_.end()) {
        continue;
      }
      // abbr_.insert(calcAbbr(s));
      abbr_to_cnt_[calcAbbr(s)]++;
      original_string_.insert(s);
    }
  }

  bool isUnique(string word) {
    const string abbr = calcAbbr(word);
    if (abbr_to_cnt_.find(abbr) == abbr_to_cnt_.end()) {
      return true;
    } else if (abbr_to_cnt_[abbr] == 1 && original_string_.find(word) != original_string_.end()) {
      return true;
    } else {
      return false;
    }
    //    if (abbr_.find(calcAbbr(word)) != abbr_.end()) {
    //      return false;
    //    } else {
    //      return true;
    //    }
  }

 private:
  // unordered_set<string> abbr_;
  unordered_map<string, int> abbr_to_cnt_;
  unordered_set<string> original_string_;
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj.isUnique(word);
 */
