class Solution {
 public:
  bool validWordSquare(vector<string>& words) {
    const int n = words.size();
    for (int i = 0; i < n; i++) {
      const string& s1 = words[i];
      if (s1.size() > n) {
        return false;
      }
      string s2;
      for (int j = 0; j < s1.size(); j++) {
        if (i >= words[j].size()) {
          return false;
        }
        s2 += words[j][i];
      }
      if (s1.compare(s2)) {
        return false;
      }
    }
    return true;
  }
};
