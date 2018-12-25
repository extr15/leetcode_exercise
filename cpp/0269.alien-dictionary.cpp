class Solution {
 public:
  bool setLess(int i, int j, vector<vector<int>>& ch_cmp) {
    unordered_set<int> less_group, great_group;
    // don't forget to insert self.
    less_group.insert(i);
    great_group.insert(j);
    for (int p = 0; p < 26; p++) {
      if (ch_cmp[i][p] == 1) {
        less_group.insert(p);
      }
      if (ch_cmp[j][p] == -1) {
        great_group.insert(p);
      }
    }
    for (auto ch1 : less_group) {
      for (auto ch2 : great_group) {
        if (ch1 == ch2) {
          return false;
        }
        if (ch_cmp[ch1][ch2] == 1) {
          return false;
        } else if (ch_cmp[ch1][ch2] == 0) {
          ch_cmp[ch1][ch2] = -1;
          ch_cmp[ch2][ch1] = 1;
        }
      }
    }
    return true;
  }
  string alienOrder(vector<string>& words) {
    vector<vector<int>> ch_cmp(26, vector<int>(26, 0));
    const int n = words.size();
    string last = words[0];
    string res;
    unordered_set<int> present_ch;
    // in case of only one string in `words`
    for(auto c : words[0]) {
      present_ch.insert(c-'a');
    }
    for (int i = 1; i < n; i++) {
      const string& cur = words[i];
      int c1 = 0, c2 = 0;
      while (c1 < last.size() && c2 < cur.size()) {
        if (last[c1] != cur[c2]) {
          int idx1 = last[c1] - 'a';
          int idx2 = cur[c2] - 'a';
          if (ch_cmp[idx1][idx2] == 1) {
            return res;
          } else if (ch_cmp[idx1][idx2] == 0) {
            bool ret = setLess(idx1, idx2, ch_cmp);
            if (!ret) {
              return res;
            }
          }
          break; // need break here, since we cannot get order from the left chars.
        }
        else {
          present_ch.insert(last[c1] - 'a');
        }
        c1++;
        c2++;
      }
      while (c1 < last.size()) {
        present_ch.insert(last[c1] - 'a');
        c1++;
      }
      while (c2 < cur.size()) {
        present_ch.insert(cur[c2] - 'a');
        c2++;
      }
      last = cur;
    }
    vector<pair<int, int>> sum_and_idx;
    for (int i = 0; i < 26; i++) {
      int have_cmp = false;
      int sum = 0;
      for (int j = 0; j < 26; j++) {
        if (ch_cmp[i][j] != 0) {
          have_cmp = true;
          sum += ch_cmp[i][j];
        }
      }
      if (have_cmp) {
        sum_and_idx.emplace_back(sum, i);
        present_ch.erase(i);
      }
    }
    std::sort(sum_and_idx.begin(), sum_and_idx.end());
    for (int i = 0; i < sum_and_idx.size(); i++) {
      res += (sum_and_idx[i].second + 'a');
    }
    for (auto c : present_ch) {
      res += (c + 'a');
    }
    return res;
  }
};
