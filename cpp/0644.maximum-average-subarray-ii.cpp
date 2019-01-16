#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Wrong.
class Solution1 {
 public:
  double findMaxAverage(vector<int>& a, int k) {
    const int n = a.size();
    int lo = 0;
    int j = 0;
    int k_sum = 0;
    while (j < k) {
      k_sum += a[j];
      j++;
    }
    double max_avg = (double)k_sum / k;
    while (true) {
      int i = lo + k;
      int sum = k_sum;
      double cur_avg = (double)sum / k;
      max_avg = max(max_avg, cur_avg);
      int cnt = k;
      while (i < n && a[i] > max_avg) {
        sum += a[i];
        cnt++;
        cur_avg = (double)sum / cnt;
        max_avg = max(max_avg, cur_avg);
        i++;
      }
      if (lo >= n - k) {
        break;
      }
      k_sum -= a[lo];
      k_sum += a[lo + k];
      lo++;
    }
    return max_avg;
  }
};

class Solution2 {
 public:
  // AC. slow.
  double findMaxAverage_BruteForce(vector<int>& a, int k) {
    const int n = a.size();
    vector<int> pre_sum(n + 1, 0);
    for (int i = 1; i < n + 1; i++) {
      pre_sum[i] = pre_sum[i - 1] + a[i - 1];
    }
    double max_avg = (double)pre_sum[k] / k;
    for (int i = 0; i <= n - k; i++) {
      for (int j = i + k; j < n + 1; j++) {
        int sum = pre_sum[j] - pre_sum[i];
        double cur_avg = (double)sum / (j - i);
        // cout << "i: " << i << ", j: " << j << ", cur_avg: " << cur_avg << endl;
        if (cur_avg > max_avg) {
          cout << "i: " << i << ", j: " << j << ", cur_avg: " << cur_avg << endl;
        }
        max_avg = max(max_avg, cur_avg);
      }
    }
    return max_avg;
  }

  double findMaxAverage_AC_slow(vector<int>& a, int k) {
    const int n = a.size();
    vector<int> pre_sum(n + 1, 0);
    for (int i = 1; i < n + 1; i++) {
      pre_sum[i] = pre_sum[i - 1] + a[i - 1];
    }
    int i = 0;
    int sum = pre_sum[k];
    double max_avg = (double)sum / k;
    while (i + k <= n) {
      // Not `i+k <= n`: a{0, 1, 1, 3, 3}; k=4;
      //      must comment here!
      //      while (i + k < n && a[i] < max_avg) {
      //        i++;
      //      }
      for (int j = i + k; j <= n; j++) {
        // `j != i+k`: a{1, 3, 1, 4, 2}; k=4;
        if (j != i + k && a[j - 1] < max_avg) {
          continue;
        }
        sum = pre_sum[j] - pre_sum[i];
        double cur_avg = (double)sum / (j - i);
        max_avg = max(max_avg, cur_avg);
      }
      i++;
    }
    return max_avg;
  }
  // AC.
  double findMaxAverage(vector<int>& a, int k) {
    const int n = a.size();
    vector<int> pre_sum(n + 1, 0);
    for (int i = 1; i < n + 1; i++) {
      pre_sum[i] = pre_sum[i - 1] + a[i - 1];
    }
    int i = 0;
    int sum = pre_sum[k];
    double max_avg = (double)sum / k;
    while (i + k <= n) {
      // Not `i+k <= n`: a{0, 1, 1, 3, 3}; k=4;
      while (i + k < n && a[i] < max_avg) {
        {
          sum = pre_sum[i + k] - pre_sum[i];
          double cur_avg = (double)sum / k;
          max_avg = max(max_avg, cur_avg);
        }
        i++;
      }
      for (int j = i + k; j <= n; j++) {
        // `j != i+k`: a{1, 3, 1, 4, 2}; k=4;
        if (j != i + k && a[j - 1] < max_avg) {
          continue;
        }
        sum = pre_sum[j] - pre_sum[i];
        double cur_avg = (double)sum / (j - i);
        max_avg = max(max_avg, cur_avg);
      }
      i++;
    }
    return max_avg;
  }
};

// AC.
class Solution3 {
 public:
  double findMaxAverage(vector<int>& a, int k) {
    const int n = a.size();
    vector<int> pre_sum(n + 1, 0);
    for (int i = 1; i < n + 1; i++) {
      pre_sum[i] = pre_sum[i - 1] + a[i - 1];
    }
    int start = 0;
    double max_avg = (double)pre_sum[k] / k;
    for (int j = k; j < n + 1; j++) {
      if (j - k != start) {
        double cur_avg = (double)(pre_sum[j - k] - pre_sum[start]) / (j - k - start);
        if (cur_avg <= max_avg) {
          start = j - k;
        }
      }
      if (pre_sum[j] - pre_sum[start] > (j - start) * max_avg) {
        for (int i = start; i <= j - k; i++) {
          double cur_avg = (double)(pre_sum[j] - pre_sum[i]) / (j - i);
          if (cur_avg > max_avg) {
            max_avg = cur_avg;
            start = i;
          }
        }
      }
    }
    return max_avg;
  }
};

// Wrong.
class Solution4 {
 public:
   // [-2, 10, -5, -5, -10, 10]; k = 4;
  double findMaxAverage_Wrong(vector<int>& a, int k) {
    const int n = a.size();
    vector<int> pre_sum(n + 1, 0);
    for (int i = 1; i < n + 1; i++) {
      pre_sum[i] = pre_sum[i - 1] + a[i - 1];
    }
    int start = 0;
    double max_avg = (double)pre_sum[k] / k;
    for (int j = k; j < n + 1; j++) {
      double cur_avg = (double)(pre_sum[j] - pre_sum[start]) / (j - start);
      double k_avg = (double)(pre_sum[j] - pre_sum[j - k]) / k;
      // error, can not just simpily drop [start, j-k].
      if (k_avg > cur_avg) {
        start = j - k;
        cur_avg = k_avg;
      }
      max_avg = max(max_avg, cur_avg);
    }
    return max_avg;
  }
  // still wrong.
  // [-2, 10, -5, -5, -10, 10]; k = 4;
  // or `test_data/0644.maximum-average-subarray-ii.data.2.txt`.
  double findMaxAverage(vector<int>& a, int k) {
    const int n = a.size();
    vector<int> pre_sum(n + 1, 0);
    for (int i = 1; i < n + 1; i++) {
      pre_sum[i] = pre_sum[i - 1] + a[i - 1];
    }
    int start = 0;
    double max_avg = (double)pre_sum[k] / k;
    for (int j = k; j < n + 1; j++) {
      double cur_avg = (double)(pre_sum[j] - pre_sum[start]) / (j - start);
      double k_avg = (double)(pre_sum[j] - pre_sum[j - k]) / k;
      if (k_avg > cur_avg) {
        for(int i=start; i<=j-k;i++) {
          cur_avg = (double)(pre_sum[j] - pre_sum[i]) / (j - i);
          if(cur_avg >= k_avg) {
            start = i;
            cur_avg = k_avg;
            break;
          }
        }
      }
      max_avg = max(max_avg, cur_avg);
    }
    return max_avg;
  }
};

int main(int argc, char* argv[]) {
  //  vector<int> a{8, 0, 1, 7, 8, 6, 5, 5, 6, 7};
  //  int k = 5;

  //  vector<int> a{0, 1, 1, 3, 3};
  //  int k = 4;

  //  vector<int> a{1, 3, 1, 4, 2};
  //  int k = 4;
  vector<int> a{-2, 10, -5, -5, -10, 10};
  int k = 4;
#if 0
  vector<int> a;
  int k;
  //const string file_name("../test_data/0644.maximum-average-subarray-ii.data.1.txt");
  const string file_name("../test_data/0644.maximum-average-subarray-ii.data.2.txt");
  // const string file_name("../test_data/test.txt");
  ifstream fin(file_name, std::ios::in);
  string line, str;
  int line_num = 0;
  while (std::getline(fin, line)) {
    stringstream ss(line);
    if (line_num == 0) {
      char ch;
      ss >> ch;
      // cout << "ch: " << ch << endl;
      // cout << "str: " << str << endl;
      int val;
      while (ss >> val) {
        // cout << "val: " << val << endl;
        a.push_back(val);
        if (ss.peek() == ',') {
          ss.ignore();
        }
      }
      // ss >> str;
    } else {
      ss >> k;
      cout << "k: " << k << endl;
    }
    line_num++;
  }
  //  cout << "a: ";
  //  for(auto v : a) {
  //    cout << v << " ";
  //  }
  //  cout << endl;
#endif
  Solution sol;
  cout << sol.findMaxAverage(a, k) << endl;
  Solution2 sol2;
  cout << sol2.findMaxAverage(a, k) << endl;
  cout << "findMaxAverage_BruteForce" << endl;
  cout << sol2.findMaxAverage_BruteForce(a, k) << endl;

  return 0;
}
