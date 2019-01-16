#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool findEqualSum(const vector<int>& a, int i, int sum) {
    const int n = a.size();
    int sum_ij = a[i + 1];
    // cout << "i: " << i << endl;
    for (int j = i + 2; j < n - 3; j++) {
      // cout << "j: " << j << ", sum_ij: " << sum_ij << endl;
      if (sum_ij == sum) {
        int sum_jk = a[j + 1];
        for (int k = j + 2; k < n - 1; k++) {
          // cout << "k: " << k << ", sum_jk: " << sum_jk << endl;
          if (sum_jk == sum) {
            int sum_kn = 0;
            for (int t = k + 1; t < n; t++) {
              sum_kn += a[t];
            }
            // cout << "sum_kn: " << sum_kn << endl;
            if (sum_kn == sum) {
              return true;
            }
          }
          sum_jk += a[k];
        }
      }
      sum_ij += a[j];
    }
    return false;
  }
  bool splitArray(vector<int>& a) {
    const int n = a.size();
    if (n < 7) {
      return false;
    }
    vector<int> filter_a;
    filter_a.reserve(a.size());
    for (int i = 0; i < n - 1; i++) {
      if (a[i] == 0 && a[i + 1] == 0) {
        continue;
      }
      filter_a.push_back(a[i]);
    }
    filter_a.push_back(a[n-1]);
    int sum = filter_a[0];
    if (filter_a.size() < 7) {
      return false;
    }
    for (int i = 1; i < filter_a.size() - 5; i++) {
      if (findEqualSum(filter_a, i, sum)) {
        return true;
      }
      sum += filter_a[i];
    }
    return false;
  }
};

int main(int argc, char* argv[]) {
  // vector<int> a{1, 2, 1, 3, 0, 0, 2, 2, 1, 3, 3};
  vector<int> a{1, 2, 1, 2, 1, 2, 1};
  Solution sol;
  cout << sol.splitArray(a) << endl;

  return 0;
}
