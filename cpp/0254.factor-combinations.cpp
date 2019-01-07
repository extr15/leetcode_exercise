#include <iostream>
#include <vector>

using namespace std;

void output2dVec(const vector<vector<int>>& v) {
  cout << "[";
  for (auto v1 : v) {
    cout << "[ ";
    for (auto v2 : v1) {
      cout << v2 << " ";
    }
    cout << "]";
  }
  cout << "]" << endl;
}

class Solution {
 public:
  vector<vector<int>> calcFactors(int n, int start) {
    vector<vector<int>> res;
    for (int i = start; i < n; i++) {
      if (n % i != 0) {
        continue;
      }
      vector<vector<int>> tmp = calcFactors(n / i, i);
      //cout << "i: " << i << endl;
      //output2dVec(tmp);
      for (auto& v : tmp) {
        v.push_back(i);
      }
      std::copy(tmp.begin(), tmp.end(), std::back_inserter(res));
    }
    if (n >= start) {
      vector<int> v;
      v.push_back(n);
      res.push_back(v);
    }
    //cout << "res: " << endl;
    //output2dVec(res);
    return res;
  }

  vector<vector<int>> getFactors(int n) {
    vector<vector<int>> res;
    res = calcFactors(n, 2);
    for (auto it = res.begin(); it != res.end();) {
      if (it->size() == 1) {
        it = res.erase(it);
      } else {
        it++;
      }
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  auto res = sol.getFactors(12);
  output2dVec(res);

  return 0;
}
