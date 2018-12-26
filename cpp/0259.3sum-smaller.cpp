class Solution {
 public:
  int threeSumSmaller(vector<int>& a, int target) {
    sort(a.begin(), a.end());
    const int n = a.size();
    int k = n - 1;
    int cnt = 0;
    while (k > 1) {
      int j=k-1;
      while(j>0) {
        int i = j - 1;
        while(i>=0) {
          if (a[i] + a[j] < target - a[k]) {
            break;
          }
          i--;
        }
        if(i == j-1) {
          cnt += (j+1)*j/2;
          break;
        }
        if(i>=0) {
          cnt += i+1;
        }
        j--;
      }
      k--;
    }
    return cnt;
  }
};


class Solution {
 public:
  int threeSumSmaller(vector<int>& a, int target) {
    sort(a.begin(), a.end());
    const int n = a.size();
    int k = n - 1;
    int cnt = 0;
    while (k > 1) {
      for (int j = k - 1; j > 0; j--) {
        for (int i = j - 1; i >= 0; i--) {
          if (a[i] + a[j] < target - a[k]) {
            cnt++;
          }
        }
      }
      k--;
    }
    return cnt;
  }
};
