#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Wrong undstanding.
class Solution1 {
 public:
  vector<int> pourWater(vector<int>& heights, int V, int K) {
//    auto cmp = [&](int i1, int i2) -> bool { return heights[i1] > heights[i2]; };
//    priority_queue<int, vector<int>, decltype(cmp) > left_pq(cmp), right_pq(cmp);
    auto leftCmp = [&](int i1, int i2) -> bool {
      if(heights[i1] == heights[i2]) {
        return i1 < i2;
      }
      return heights[i1] > heights[i2];
    };
    auto rightCmp = [&](int i1, int i2) -> bool {
      if(heights[i1] == heights[i2]) {
        return i1 > i2;
      }
      return heights[i1] > heights[i2];
    };
    priority_queue<int, vector<int>, decltype(leftCmp) > left_pq(leftCmp);
    priority_queue<int, vector<int>, decltype(rightCmp) > right_pq(rightCmp);
    for (int i = 0; i < K; i++) {
      left_pq.push(i);
    }
    const int n = heights.size();
    for (int i = n - 1; i > K; i--) {
      right_pq.push(i);
    }
    while (V > 0) {
      int cur = heights[K];
      bool has_add = false;
      if (!left_pq.empty()) {
        int left = left_pq.top();
        if (heights[left] < cur) {
          left_pq.pop();
          heights[left]++;
          left_pq.push(left);
          has_add = true;
        }
      }
      if (!has_add && !right_pq.empty()) {
        int right = right_pq.top();
        if (heights[right] < cur) {
          right_pq.pop();
          heights[right]++;
          right_pq.push(right);
          has_add = true;
        }
      }
      if (!has_add) {
        heights[K]++;
      }
      V--;
    }
    return heights;
  }
};

// AC.
class Solution2 {
 public:
  vector<int> pourWater(vector<int>& heights, int V, int K) {
    const int n = heights.size();
    while(V > 0) {
      V--;
      int cur = heights[K];
      // check moving to left.
      int right_most = K;
      int i = K-1;
      while(i >=0 && heights[i] <= cur) {
        if(heights[i] < cur) {
          cur = heights[i];
          right_most = i;
        }
        i--;
      }
      if(cur < heights[K]) {
        heights[right_most]++;
        continue;
      }
      // check moving to right.
      int left_most = K;
      i = K+1;
      while (i < n && heights[i] <= cur) {
        if(heights[i] < cur) {
          cur = heights[i];
          left_most = i;
        }
        i++;
      }
      heights[left_most]++;
    }
    return heights;
  }
};

// AC, a little faster.
class Solution {
 public:
   int findNextLeft(const vector<int>& heights, int K) {
     int cur = heights[K];
     int right_most = K;
     int i = K-1;
     while(i>=0 && heights[i] <= cur) {
       if(heights[i] < cur) {
         cur = heights[i];
         right_most = i;
       }
       i--;
     }
     return right_most;
   };
   int findNextRight(const vector<int>& heights, int K) {
     int cur = heights[K];
     int left_most = K;
     int i = K+1;
     const int n = heights.size();
     while(i < n && heights[i] <= cur) {
       if(heights[i] < cur) {
         cur = heights[i];
         left_most = i;
       }
       i++;
     }
     return left_most;
   };

  vector<int> pourWater(vector<int>& heights, int V, int K) {
    //const int n = heights.size();
    int next_left = findNextLeft(heights, K);
    int next_right = findNextRight(heights, K);
    while(V > 0) {
      V--;
      //cout << "next_left: " << next_left << ", next_right: " << next_right << ", K: " <<  K << endl;
      if(next_left < K) {
        heights[next_left]++;
        int origin_left = next_left;
        // the commented code is the same as `findNextLeft`.
//        int h = heights[next_left];
//        int i = next_left - 1;
//        while(i >=0 && heights[i] <= h) {
//          if(heights[i] < h) {
//            h = heights[i];
//            next_left = i;
//          }
//          i--;
//        }
        next_left = findNextLeft(heights, origin_left);
        if(next_left == origin_left) {
          while(next_left <=K-1 && heights[next_left] == heights[next_left+1]) {
            next_left++;
          }
        }
      }
      else if(next_right > K) {
        heights[next_right]++;
        int origin_right = next_right;
        next_right = findNextRight(heights, origin_right);
        if(next_right == origin_right) {
          while(next_right >= K+1 && heights[next_right] == heights[next_right-1]) {
            next_right--;
          }
        }
      }
      else {
        heights[K]++;
        next_left = findNextLeft(heights, K);
        next_right = findNextRight(heights, K);
      }
    }
    return heights;
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  vector<int> h{ 1,2,3,4,3,2,1,2,3,4,3,2,1 };
  int v= 2, k = 5;
  auto res = sol.pourWater(h, v, k);
  for(int i=0; i< res.size(); i++) {
    cout << res[i] << " ";
  }
  cout << endl;
  return 0;
}
