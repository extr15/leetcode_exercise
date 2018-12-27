class Solution {
 public:
  vector<int> anagramMappings(vector<int>& A, vector<int>& B) {
    map<int, int> val_to_idx;
    for (int i = 0; i < B.size(); i++) {
      val_to_idx.insert({B[i], i});
    }

    vector<int> res;
    for (int i = 0; i < A.size(); i++) {
      res.push_back(val_to_idx[A[i]]);
    }
    return res;
  }
};
