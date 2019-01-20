#include <deque>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;
// AC. slow
class Solution1 {
 public:
  int kEmptySlots(vector<int>& flowers, int k) {
    const int n = flowers.size();
    vector<bool> bloom(n, false);
    for (int day = 0; day < n; day++) {
      if (n - day <= k) {
        break;
      }
      bloom[flowers[day] - 1] = true;
      int prev_bloom = -1;
      for (int pos = 0; pos < n; pos++) {
        if (!bloom[pos]) {
          continue;
        }
        if (prev_bloom < 0) {
          prev_bloom = pos;
        } else {
          if (pos - prev_bloom == k + 1) {
            // day index is start from 1.
            return day + 1;
          } else {
            prev_bloom = pos;
          }
        }
      }
    }
    return -1;
  }
};

// TLE when k is large.
class Solution2 {
 public:
  int kEmptySlots(vector<int>& flowers, int k) {
    const int n = flowers.size();
    vector<bool> bloom(n, false);
    // all valid candidate blooming position and it's valid count.
    unordered_map<int, int> candidate_pos_to_cnt;
    // pos and if it's left and right candidate is valid or not.
    // pos_left is `pos - k -1`, pos_right is `pos + k + 1`.
    // unordered_map<pos, pair<pos_left_is_valid_candidate, pos_right_is_valid_candidate> >.
    unordered_map<int, pair<bool, bool> > pos_to_candidate_valid;
    for (int day = 0; day < n; day++) {
      if (n - day <= k) {
        break;
      }
      int cur_pos = flowers[day] - 1;
      bloom[cur_pos] = true;
      if (candidate_pos_to_cnt.find(cur_pos) != candidate_pos_to_cnt.end()) {
        return day + 1;
      }
      bool left_candidate_valid = true;
      int cur_left = cur_pos - k - 1;
      if (cur_left < 0) {
        left_candidate_valid = false;
      }
      for (int pos = max(cur_left, 0); pos < cur_pos; pos++) {
        if (bloom[pos]) {
          left_candidate_valid = false;
          auto& valid = pos_to_candidate_valid[pos];
          if (valid.second == true) {
            valid.second = false;
            int pos_right = pos + k + 1;
            candidate_pos_to_cnt[pos_right]--;
            if (candidate_pos_to_cnt[pos_right] == 0) {
              candidate_pos_to_cnt.erase(pos_right);
            }
          }
        }
      }
      // left_candidate_valid && cur_left >=0
      if (left_candidate_valid) {
        candidate_pos_to_cnt[cur_left]++;
      }
      bool right_candidate_valid = true;
      int cur_right = cur_pos + k + 1;
      if (cur_right >= n) {
        right_candidate_valid = false;
      }
      for (int pos = cur_pos + 1; pos <= min(cur_right, n - 1); pos++) {
        if (bloom[pos]) {
          right_candidate_valid = false;
          auto& valid = pos_to_candidate_valid[pos];
          if (valid.first == true) {
            valid.first = false;
            int pos_left = pos - k - 1;
            candidate_pos_to_cnt[pos_left]--;
            if (candidate_pos_to_cnt[pos_left] == 0) {
              candidate_pos_to_cnt.erase(pos_left);
            }
          }
        }
      }
      if (right_candidate_valid) {
        candidate_pos_to_cnt[cur_right]++;
      }
      pos_to_candidate_valid[cur_pos] =
          pair<bool, bool>(left_candidate_valid, right_candidate_valid);
    }
    return -1;
  }
};

// AC. map.
class Solution3 {
 public:
  int kEmptySlots(vector<int>& flowers, int k) {
    const int n = flowers.size();
    vector<bool> bloom(n, false);
    // map<segment_first, segment_last>
    map<int, int> candidate_segment;
    candidate_segment.insert({0, n - 1});
    for (int day = 0; day < n; day++) {
      if (n - day <= k) {
        break;
      }
      int cur_pos = flowers[day] - 1;
      bloom[cur_pos] = true;
      // cout << "day: " << day << ", cur_pos: "  << cur_pos << endl;
      // auto lb = candidate_segment.lower_bound(cur_pos);
      auto ub = candidate_segment.upper_bound(cur_pos);
      // otherwise maybe segment fault.
      if (ub == candidate_segment.begin()) {
        continue;
      }
      ub--;
      if (ub == candidate_segment.end() || ub->second < cur_pos) {
        // cout << "d1" << endl;
        continue;
      }
      int left = ub->first, right = ub->second;
      candidate_segment.erase(left);
      // cout << "day: " << day << ", cur_pos: "  << cur_pos << ", left: " << left << ", right: " <<
      // right << endl;
      if ((left != 0 && cur_pos - left == k) || (right != n - 1 && right - cur_pos == k)) {
        return day + 1;
      }
      if (cur_pos - left > k) {
        candidate_segment.insert({left, cur_pos - 1});
      }
      if (right - cur_pos > k) {
        candidate_segment.insert({cur_pos + 1, right});
      }
      if (candidate_segment.empty()) {
        return -1;
      }
    }
    return -1;
  }
};

// AC. MinQueue.
class Solution {
 public:
  struct Elem {
    Elem(int v, int i) : val(v), idx(i){};
    int val;
    int idx;
  };
  // minimun is the first.
  template <typename T>
  class MinQueue {
   public:
    void push(const T& v) {
      while (!data.empty() && data.back().val >= v.val) {
        data.pop_back();
      }
      data.push_back(v);
    }
    void pop(int idx_threshold) {
      while (!data.empty() && data.front().idx <= idx_threshold) {
        data.pop_front();
      }
    }
    const T& min() const { return data.front(); }
    bool empty() const { return data.empty(); }

   private:
    deque<T> data;
  };
  int kEmptySlots(vector<int>& flowers, int k) {
    const int n = flowers.size();
    vector<int> days(n);
    for (int i = 0; i < n; i++) {
      days[flowers[i] - 1] = i;
    }
    MinQueue<Elem> mq;
    for (int i = 1; i <= k; i++) {
      mq.push(Elem(days[i], i));
    }
    int min_day = n;
    for (int j = k + 1; j < n; j++) {
      int i = j - k - 1;
      int win_min;
      if (mq.empty()) {
        win_min = n;
      } else {
        win_min = mq.min().val;
      }
      if (days[i] < win_min && days[j] < win_min) {
        min_day = min(min_day, max(days[i], days[j]));
      }
      mq.push(Elem(days[j], j));
      mq.pop(j - k);
    }
    if (min_day == n) {
      return -1;
    } else {
      return min_day + 1;
    }
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  // vector<int> a{1, 3, 2};
  //  vector<int> a{1, 2, 3};
  //  int k = 1;

  vector<int> a{9, 1, 4, 2, 8, 7, 5, 3, 6, 10};
  int k = 3;
  cout << sol.kEmptySlots(a, k) << endl;
  return 0;
}
