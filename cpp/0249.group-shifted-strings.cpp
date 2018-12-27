// Failed: Wrong problem understanding.
class Solution {
 public:
  string shiftString(const string s) {
    int i = 0;
    string s2(s);
    for (; i < s2.size() - 1; i++) {
      s2[i] = s[i + 1];
    }
    s2[i] = s2[i] + 1;
    return s2;
  }
  vector<vector<string>> groupStrings(vector<string>& strings) {
    unordered_map<string, int> str_to_id;
    for (auto s : strings) {
      str_to_id.insert({s, -1});
    }
    int id = 0;
    vector<vector<string>> res;
    for (auto s : strings) {
      if (s.empty()) {
        continue;
      }
      if (str_to_id[s] != -1) {
        continue;
      }
      vector<string> same_group;
      same_group.push_back(s);
      bool find_group = false;
      while (s[s.size() - 1] != 'z') {
        string s2 = shiftString(s);
        if (str_to_id.find(s2) != str_to_id.end()) {
          if (str_to_id[s2] != -1) {
            find_group = true;
            str_to_id[s] = str_to_id[s2];
            res[str_to_id[s2]].push_back(s);
            break;
          } else {
            same_group.push_back(s2);
          }
        }
        s = s2;
      }
      if (find_group) {
        continue;
      }
      res.push_back(vector<string>());
      for (auto s_tmp : same_group) {
        str_to_id[s_tmp] = id;
        res[id].push_back(s_tmp);
      }
      id++;
    }

    return res;
  }
};
