// AC.
class Solution {
 public:
  vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    vector<int> res(length, 0);
    for (auto& up : updates) {
      int low = max(0, up[0]);
      int high = min(length - 1, up[1]);
      for (int i = low; i <= high; i++) {
        res[i] += up[2];
      }
    }
    return res;
  }
};

// AC.
class Solution {
 public:
  vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    vector<int> res(length, 0);
    for (auto& up : updates) {
      int low = max(0, up[0]);
      res[low] += up[2];
      if(up[1]+1 < length) {
        int high = up[1]+1;
        res[high] -= up[2];
      }
    }
    int sum = 0;
    for(int i=0;i<length;i++) {
      res[i] += sum;
      sum = res[i];
    }
    return res;
  }
};

class Solution {
 public:
   void updateSegmentTree(vector<int>& tree, vector<bool>& lazy, int low, int high, int val) {
     ;
   }
  vector<int> getModifiedArray(int n, vector<vector<int>>& updates) {
    vector<int> res(n, 0);
    vector<int> tree(2*n, 0);
    vector<bool> lazy(2*n, false);
    buildSegmentTree();
    for (auto& up : updates) {
      int low = max(0, up[0]);
      int high = min(length - 1, up[1]);
      updateSegmentTree(tree, lazy, low, high, up[2]);
    }
  }
};
