class Solution {
 public:
  const string& findAncestor(const string& s, unordered_map<string, string>& ancestor) {
    if (ancestor.find(s) == ancestor.end()) {
      return s;
    }
    if (ancestor[s] != s) {
      ancestor[s] = findAncestor(ancestor[s], ancestor);
    }
    return ancestor[s];
  }
  bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2,
                              vector<pair<string, string>> pairs) {
    if (words1.size() != words2.size()) {
      return false;
    }
    unordered_map<string, string> ancestor;
    unordered_map<string, int> grade;
    for (auto& p : pairs) {
      const string& a1 = findAncestor(p.first, ancestor);
      const string& a2 = findAncestor(p.second, ancestor);
      if (a1 != a2) {
        if (grade[a1] > grade[a2]) {
          ancestor[a2] = a1;
        } else if (grade[a1] < grade[a2]) {
          ancestor[a1] = a2;
        } else {
          ancestor[a2] = a1;
          grade[a1]++;
        }
      }
    }

    const int n = words1.size();
    for (int i = 0; i < n; i++) {
      const string& w1 = words1[i];
      const string& w2 = words2[i];
      if (w1 != w2) {
        const string& a1 = findAncestor(w1, ancestor);
        const string& a2 = findAncestor(w2, ancestor);
        if (a1 != a2) {
          return false;
        }
      }
    }
    return true;
  }
};
