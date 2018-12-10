/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
// AC
class Solution {
 public:
  vector<Interval> merge(vector<Interval>& intervals) {
    const int n = intervals.size();
    if (n < 2) {
      return intervals;
    }
    std::sort(intervals.begin(), intervals.end(),
              [&](const Interval& a, const Interval& b) { return a.start < b.start; });
    vector<Interval> res;
    Interval cur = intervals[0];
    for (int i = 1; i < n; i++) {
      if (intervals[i].start > cur.end) {
        res.push_back(cur);
        cur = intervals[i];
      } else {
        cur.end = std::max(cur.end, intervals[i].end);
      }
    }
    res.push_back(cur);
    return res;
  }
};

// AC
class Solution {
 public:
  vector<Interval> merge(vector<Interval>& intervals) {
    const int n = intervals.size();
    if (n < 2) {
      return intervals;
    }
    map<int, std::pair<int, int>> num_to_start_end_cnt; // map<num, pair<as_start_cnt, as_end_cnt>>;
    for(int i=0; i<n; i++) {
      num_to_start_end_cnt[intervals[i].start].first++;
      num_to_start_end_cnt[intervals[i].end].second++;
    }
    vector<Interval> res;
    Interval cur;
    int start_cnt = 0;
    bool update_start = true;
    for(auto& m : num_to_start_end_cnt) {
      if(update_start) {
        cur.start = m.first;
        update_start = false;
      }
      auto start_end_cnt = m.second; 
      if(start_end_cnt.first >0) {
        start_cnt += start_end_cnt.first;
      }
      // Not `else if`.
      if(start_end_cnt.second > 0) {
        start_cnt -= start_end_cnt.second;
        if(start_cnt ==0) {
          cur.end = m.first;
          res.push_back(cur);
          update_start = true;
        }
      }
    }
    return res;
  }
};
