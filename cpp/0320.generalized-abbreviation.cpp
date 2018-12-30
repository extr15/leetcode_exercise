// Wrong understanding.
class Solution {
 public:
  vector<string> generateAbbreviations(string word) {
    const int n = word.size();
    vector<string> res;
    res.push_back(word);
    for (int k = 1; k < n; k++) {
      string cur_k = std::to_string(k);
      for (int i = k; i < n; i++) {
        string cur = word.substr(0, i - k) + cur_k + word.substr(k, n - i);
        res.push_back(cur);
      }
    }
    res.push_back(std::to_string(n));
    return res;
  }
};


// AC. iterative.
class Solution {
 public:
  vector<string> generateAbbreviations(string word) {
    const int n = word.size();
    vector<string> res;
    vector<int> last_cnt;
    res.push_back("");
    last_cnt.push_back(0);
    for(int i=0;i<n;i++) {
      vector<string> tmp;
      vector<int> cur_cnt;
      for(int j=0;j<res.size();j++) {
        string cur = res[j] + word[i];
        tmp.push_back(cur);
        cur_cnt.push_back(0);
        if(last_cnt[j] == 0) {
          cur = res[j] + "1";
          tmp.push_back(cur);
          cur_cnt.push_back(1);
        }
        else {
          int to_erase = last_cnt[j] / 10 + 1;
          cur = res[j].substr(0, res[j].size()-to_erase) + std::to_string(last_cnt[j]+1);
          tmp.push_back(cur);
          cur_cnt.push_back(last_cnt[j]+1);
        }
      }
      std::swap(res, tmp);
      std::swap(last_cnt, cur_cnt);
    }
    return res;
  }
};

// AC. recursive
class Solution {
 public:
  void calcAbbr(const string& word, int idx, int last_cnt, string cur, vector<string>& res) {
    const int n = word.size();
    if (idx == n) {
      if (last_cnt != 0) {
        cur += std::to_string(last_cnt);
      }
      res.push_back(cur);
      return;
    }

    string next1 = cur;
    if (last_cnt == 0) {
      next1 += word[idx];
    } else {
      next1 += (std::to_string(last_cnt) + word[idx]);
    }
    calcAbbr(word, idx + 1, 0, next1, res);

    calcAbbr(word, idx + 1, last_cnt + 1, cur, res);
  }
  vector<string> generateAbbreviations(string word) {
    const int n = word.size();
    vector<string> res;
    calcAbbr(word, 0, 0, "", res);
    return res;
  }
};

