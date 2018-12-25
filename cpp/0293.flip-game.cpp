class Solution {
 public:
  vector<string> generatePossibleNextMoves(string s) {
    vector<string> res;
    const int n = s.size();
    if (n < 2) {
      return res;
    }
    for (int i = 1; i < n; i++) {
      string tmp(s);
      if (s[i - 1] == '+' && s[i] == '+') {
        tmp[i - 1] = '-';
        tmp[i] = '-';
        res.push_back(tmp);
      }
    }
    return res;
  }
};
