class Solution {
 public:
  vector<int> calcNext(const string& p) {
    const int n = p.size();
    vector<int> next(n, -1);
    next[0] = -1;
    int j = 0, k = -1;
    while (j < n - 1) {
      if (k == -1 || p[j] == p[k]) {
        k++;
        j++;
        next[j] = k;
      } else {
        k = next[k];
      }
    }
    return next;
  }
  vector<int> kmpSearchRepeat(const string& s, const string& p) {
    vector<int> next = calcNext(p);
    const int m = s.size();
    const int n = p.size();
    int i = 0, j = 0;
    vector<int> match_idx;
    while (i < m && j < n) {
      if (j == -1 || s[i] == p[j]) {
        i++;
        j++;
        if (j == n) {
          int idx = i - j;
          match_idx.push_back(idx);
          i = idx + 1;
          j = 0;
        }
      } else {
        j = next[j];
      }
    }
    return match_idx;
  }
  string boldWords(vector<string>& words, string s) {
    const int m = s.size();
    vector<bool> bold(m, false);
    for (auto& w : words) {
      auto match_idx = kmpSearchRepeat(s, w);
      const int n = w.size();
      for (auto idx : match_idx) {
        for (int i = idx; i < idx + n; i++) {
          bold[i] = true;
        }
      }
    }
    string res;
    bool start_bold = false;
    for (int i = 0; i < m; i++) {
      if (!start_bold && bold[i]) {
        start_bold = true;
        res += "<b>";
      }
      if (start_bold && !bold[i]) {
        res += "</b>";
        start_bold = false;
      }
      res += s[i];
    }
    if (start_bold) {
      res += "</b>";
    }
    return res;
  }
};
