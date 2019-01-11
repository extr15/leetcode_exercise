#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    if (k <= 0) {
      return vector<int>();
    }
    vector<vector<int>> res(k+1);
    for (auto v : res) {
      v.reserve(1000);
    }
    const int m = nums1.size();
    const int n = nums2.size();
    int cnt = 0;
    for (int i = 0; i <= k; i++) {
      if (i > m || k - i > n) {
        continue;
      }
      cout << "i: " << i << ", k: " << k << endl;
      vector<int> max_1, max_2;
      findMaxKNumber(nums1, i, &max_1);
      findMaxKNumber(nums2, k - i, &max_2);
      cout << "max_1.size: " << max_1.size() << endl;
      cout << "max_2.size: " << max_2.size() << endl;
      vector<int> max_res;
      mergeMax(max_1, max_2, &max_res);
      cout << "max_res.size: " << max_res.size() << endl;
      //res.push_back(max_res);
      res[cnt] = max_res; // Not `res[i]`
      cnt++;
    }
    cout << "cnt: " << cnt << endl;
    return findMaxFromVector(res, cnt, k);
  }

  vector<int> findMaxFromVector(const vector<vector<int>>& res, int cnt, int k) {
    std::list<int> idx;
    cout << "res.size: " << res.size() << endl;
    for (int i = 0; i < cnt; i++) {
      idx.push_back(i);
    }
    for (int i = 0; i < k; i++) {
      cout << "i: " << i << endl;
      if (idx.size() == 1) {
        break;
      }
      int max_val = -1;
      for (auto j : idx) {
        cout << "res[j].size: " << res[j].size() << ", j: " << j << endl;
        if (res[j][i] > max_val) {
          max_val = res[j][i];
        }
      }
      for (auto jt = idx.begin(); jt != idx.end();) {
        if (res[*jt][i] != max_val) {
          jt = idx.erase(jt);
        } else {
          jt++;
        }
      }
    }
    cout << "idx.size: " << idx.size() << endl;
    if (idx.size() > 0) {
      cout << *(idx.begin()) << endl;
      return res[*(idx.begin())];
    } else {
      return vector<int>();
    }
  }
  // k maybe zero, then return an empty vector.
  void findMaxKNumber(const std::vector<int>& v, int k, std::vector<int>* res) {
    res->clear();
    const int n = v.size();
    int start = 0;
    for (int i = 0; i < k; i++) {
      int max_val = -1;
      int max_j;
      for (int j = start; j < n - (k - i) + 1; j++) {
        if (v[j] > max_val) {
          max_val = v[j];
          max_j = j;
        }
      }
      start = max_j + 1;
      res->push_back(max_val);
    }
    return;
  }
  void mergeMax(const std::vector<int>& v1, const std::vector<int>& v2,
                std::vector<int>* res) {
       const int m = v1.size();
    const int n = v2.size();
    int i = 0, j = 0;
    res->clear();
    while (i < m || j < n) {
      if(isGreater(v1, i, v2, j)) {
        res->push_back(v1[i]);
        i++;
      }
      else {
        res->push_back(v2[j]);
        j++;
      }
    }
  }
  bool isGreater(const std::vector<int>& v1, int i, const std::vector<int>& v2, int j) {
    const int m = v1.size();
    const int n = v2.size();
    while(i<m && j<n && v1[i] == v2[j]) {
      i++;
      j++;
    }
    if(j == n) {
      return true;
    }
    if(i == m) {
      return false;
    }
    return v1[i] > v2[j];
  }
  void mergeMax_bug(const std::vector<int>& v1, const std::vector<int>& v2,
                std::vector<int>* res) {
    const int m = v1.size();
    const int n = v2.size();
    int i = 0, j = 0;
    res->clear();
    while (i < m || j < n) {
      const int a = (i < m) ? v1[i] : -1;
      const int b = (j < n) ? v2[j] : -1;
      if (a > b) {
        res->push_back(a);
        if (i < m) {
          i++;
        }
      }
      else if( a<b ) {
        res->push_back(b);
        if (j < n) {
          j++;
        }
      }
      else { // a == b
        int i2 = i, j2 = j;
        cout << "i: " << i << ", j: " << j << endl;
        while(i2 <m || j2 < n) {
          cout << "i2: " << i2 << ", j2: " << j2 << endl;
          i2 = (i2 < m) ? i2+1 : i2;
          j2 = (j2 < n) ? j2+1 : j2;
          cout << "i2: " << i2 << ", j2: " << j2 << endl;
        int a2 = (i2 < m) ? v1[i2] : -1;
        int b2 = (j2 < n) ? v2[j2] : -1;
          cout << "a2: " << a2 << ", b2: " << b2 << endl;
        if(a2 >= b2) {
          if( a2 > a ) {
            for(int i3 = i; i3<i2; i3++) {
              res->push_back(a);
            }
            res->push_back(a2);
            i = i2+1;
            break;
          }
          else if(a2 <= a) {
            for(int i3 = i; i3 < i2; i3++) {
              res->push_back(a);
            }
            for(int j3 = j; j3 < j2; j3++) {
              res->push_back(a);
            }
            i = i2;
            j = j2;
            if(a2 < a) {
              break;
            }
          }
        }
        else {
          if( b2 > a ) {
            for(int j3 = j; j3<j2; j3++) {
              res->push_back(a);
            }
            res->push_back(b2);
            j = j2+1;
            break;
          }
          else if(b2 <= a) {
            for(int i3 = i; i3 < i2; i3++) {
              res->push_back(a);
            }
            for(int j3 = j; j3 < j2; j3++) {
              res->push_back(a);
            }
            i = i2;
            j = j2;
            if(b2 < a) { // v1{5}, v2{5, 2}, k=3;
              break;
            }
          }

        }
        if(a2 != b2) {
          break;
        }
        }
      
       /* 
        int i2 = i + 1, j2 = j + 1;
        while(i2 < m && v1[i2] == a) {
          i2++;
        }
        int a2 = (i2 < m) ? v1[i2] : a;

        while(j2 < n && v2[j2] == b) {
          j2++;
        }
        int b2 = (j2 < n) ? v2[j2] : b;
        if(a2 >= b2) {
          if(a >= a2) {
            for(int i3 = i; i3 < i2; i3++) {
              res->push_back(a);
            }
            for(int j3 = j; j3 < j2; j3++) {
              res->push_back(a);
            }
            i = i2;
            j = j2;
          }
          else {
            for(int i3 = i; i3 < i2; i3++) {
              res->push_back(a);
            }
            res->push_back(a2);
            i = i2+1;
          }
        }
        else {
          if(a >= b2) {
            for(int i3 = i; i3 < i2; i3++) {
              res->push_back(a);
            }
            for(int j3 = j; j3 < j2; j3++) {
              res->push_back(a);
            }
            i = i2;
            j = j2;
          }
          else {
            for(int j3 = j; j3 < j2; j3++) {
              res->push_back(a);
            }
            res->push_back(b2);
            j = j2+1;
          }
        }
        */
        
        }

    }
  }
};

int main(int argc, char* argv[]) {
//vector<int> v1{3, 4, 6, 5}, v2{9, 1, 2, 5, 8, 3};
// [9 8 6 5 3]
// vector<int> v1{6, 7}, v2{6, 0, 4};
// [6 7 6 0 4]
// int k = 5;
//vector<int> v1{3, 9}, v2{8, 9};
//int k = 3;
// [9, 8, 9]
//  vector<int> v1{1,6,5,4,7,3,9,5,3,7,8,4,1,1,4}, v2{4,3,1,3,5,9};
//  int k = 21;
  // [4,3,1,6,5,4,7,3,9,5,3,7,8,4,1,3,5,9,1,1,4]

  //vector<int> v1{}, v2{};
  //vector<int> v1{5, 1, 0}, v2{5, 2, 1};
  //vector<int> v1{5}, v2{5, 2};
  //int k = 3;
  //vector<int> v1{3, 8, 5, 3, 4}, v2{8, 7, 3, 6, 8};
  //vector<int> v1{ 8, 5, 4}, v2{8, 8};
  //int k = 5;
  //
//  vector<int> v1{5,0,2,1,0,1,0,3,9,1,2,8,0,9,8,1,4,7,3}, v2{7,6,7,1,0,1,0,5,6,0,5,0};
//  int k = 31;
  vector<int> v1{0, 1, 0, 3}, v2{0, 1, 0, 5};
  int k = 8;

  Solution solution;
  auto res = solution.maxNumber(v1, v2, k);
  cout << "res: ";
  for (auto v : res) {
    cout << v << " ";
  }
  cout << endl;

  return 0;
}
