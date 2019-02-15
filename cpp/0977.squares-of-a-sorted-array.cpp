
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> sortedSquares(vector<int>& a) {
    vector<int> res;
    if (a.empty()) {
      return res;
    }
    const int n = a.size();
    int i = 0, j = n - 1;
    int si = a[i] * a[i];
    int sj = a[j] * a[j];

    while (i <= j) {
      if (si > sj) {
        res.push_back(si);
        i++;
        si = a[i] * a[i];
      } else {
        res.push_back(sj);
        j--;
        sj = a[j] * a[j];
      }
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

int main(int argc, char* argv[]) { return 0; }
