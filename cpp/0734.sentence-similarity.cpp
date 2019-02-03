class Solution {
 public:
  bool areSentencesSimilar(vector<string>& words1, vector<string>& words2,
                           vector<pair<string, string>> pairs) {
    if (words1.size() != words2.size()) {
      return false;
    }
    unordered_map<string, unordered_set<string>> similiar;
    for (auto& p : pairs) {
      similiar[p.first].insert(p.second);
      similiar[p.second].insert(p.first);
    }
    const int n = words1.size();
    for (int i = 0; i < n; i++) {
      const string& w1 = words1[i];
      const string& w2 = words2[i];
      if (w1 != w2) {
        if (similiar.find(w1) != similiar.end()) {
          auto& sim = similiar[w1];
          if (sim.find(w2) == sim.end()) {
            return false;
          }
        }
        else {
          return false;
        }
      }
    }
    return true;
  }
};

/* 
["a","very","delicious","meal"]
["one","really","good","dinner"]
[["great","good"],["extraordinary","good"],["well","good"],["wonderful","good"],["excellent","good"],["fine","good"],["nice","good"],["any","one"],["some","one"],["unique","one"],["the","one"],["an","one"],["single","one"],["a","one"],["truck","car"],["wagon","car"],["automobile","car"],["auto","car"],["vehicle","car"],["entertain","have"],["drink","have"],["eat","have"],["take","have"],["fruits","meal"],["brunch","meal"],["breakfast","meal"],["food","meal"],["dinner","meal"],["super","meal"],["lunch","meal"],["possess","own"],["keep","own"],["have","own"],["extremely","very"],["actually","very"],["really","very"],["super","very"]]

 * */
