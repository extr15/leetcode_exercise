class Solution {
 public:
  string rearrangeString(string s, int k) {
    if (k == 0) {
      return s;
    }
    const int n = s.size();
    unordered_map<char, int> ch_to_cnt;
    for (int i = 0; i < n; i++) {
      ch_to_cnt[s[i]]++;
    }
    string res;
    int i = 0;
    vector<bool> used(256, false);
    while (i < n) {
      int max_cnt = 0;
      char ch;
      for (auto& elem : ch_to_cnt) {
        if (elem.second > max_cnt && !used[elem.first]) {
          max_cnt = elem.second;
          ch = elem.first;
        }
      }
      if (max_cnt == 0) {
        return "";
      }
      res += ch;
      ch_to_cnt[ch]--;
      if (ch_to_cnt[ch] == 0) {
        ch_to_cnt.erase(ch);
      }
      used[ch] = true;
      i++;
      if (i >= k) {
        used[res[i - k]] = false;
      }
    }

    return res;
  }
};

