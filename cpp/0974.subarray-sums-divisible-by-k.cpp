#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution1 {
public:
    int subarraysDivByK(vector<int>& a, int K) {
      const int n = a.size();
      vector<int> sum(n+1, 0);
      sum[0]= 0;
      for(int i=1; i<n+1; i++) {
        sum[i] = sum[i-1] + a[i-1];
      }
      int cnt = 0;
      for(int i=0;i<n;i++) {
        for(int j=i+1; j<n+1; j++) {
          int d = sum[j] - sum[i];
          if(d == 0 || d % K == 0) {
            cnt++;
          }
        }
      }
      return cnt;
        
    }
};

class Solution {
public:
    int subarraysDivByK(vector<int>& a, int K) {
      const int n = a.size();
      vector<int> sum(n+1, 0);
      sum[0]= 0;
      for(int i=1; i<n+1; i++) {
        sum[i] = sum[i-1] + a[i-1];
      }
      vector<int> cnt(n+1, 0);
      vector<int> last_idx(n+1, 0);
      for(int j=1; j<n+1; j++) {
        for(int i=j-1; i>=0; i--) {
          int d = sum[j] - sum[i];
          if(d % K == 0) {
            cnt[j] = cnt[i] +1;
            last_idx[j] = i;
            //cout << "j: " << j << ", cnt[j]: " << cnt[j] << ", i: " << i<< endl;
            break;
          }
        }
      }

      int total = 0;
      for(int i=0;i<n+1; i++) {
        total += cnt[i];
      }
      return total;

      int j=n;
      int last = last_idx[j];
      while(j>0 && j > last) {
        total += cnt[j];
        j--;
        last = max(last, last_idx[j]);
      }
      return total;
    }
};
int main(int argc, char *argv[]) {
  Solution sol;
  vector<int> a{4,5,0,-2,-3,1};
  // 0, 4, 9, 0, 7, 4, 1
  // 0, 1, 2, 3, 4, 5, 6
  // [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
  cout << sol.subarraysDivByK(a, 5) << endl;
    return 0;
}
