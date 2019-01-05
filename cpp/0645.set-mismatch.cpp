// AC.
class Solution {
 public:
  vector<int> findErrorNums(vector<int>& a) {
    const int n = a.size();
    int i = 0;
    while (i < n) {
      while (i < n && a[a[i] - 1] != a[i]) {
        swap(a[a[i] - 1], a[i]);
      }
      i++;
    }
    vector<int> res;
    i = 0;
    while (i < n) {
      if (a[i] != i + 1) {
        res.push_back(a[i]);
        res.push_back(i + 1);
        break;
      }
      i++;
    }
    return res;
  }
};

// Wrong for [8,7,3,5,3,6,1,4].
class Solution {
 public:
  vector<int> findErrorNums(vector<int>& a) {
    const int n = a.size();
    int i = 0;
    vector<int> res;
    while (i < n) {
      while (i < n && a[a[i] - 1] != a[i]) {
        swap(a[a[i] - 1], a[i]);
      }
      if(a[i] != i+1) {
        res.push_back(a[i]);
        res.push_back(i + 1);
        break;
      }
      i++;
    }
    return res;
  }
};

