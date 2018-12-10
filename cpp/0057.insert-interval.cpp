/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
 public:
  vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    const int n = intervals.size();
    vector<Interval> res;
    if (n == 0) {
      res.push_back(newInterval);
      return res;
    }
    int start_pos = -1;
    bool overlapping_start = false;
    for (int i = 0; i < n; i++) {
      if (newInterval.start <= intervals[i].end) {
        if (newInterval.start >= intervals[i].start) {
          overlapping_start = true;
          start_pos = i;
        } else {
          start_pos = i - 1;
          overlapping_start = false;
        }
        break;
      } else {
        res.push_back(intervals[i]);
      }
    }
    int end_pos = start_pos;
    bool overlapping_end = false;
    for (int j = std::max(start_pos, 0); j < n; j++) {
      if (newInterval.end >= intervals[j].start) {
        if (newInterval.end <= intervals[j].end) {
          end_pos = j;
          overlapping_end = true;
          break;
        } else {
          end_pos = j;
          overlapping_end = false;
        }
      } else {
        break;
      }
    }
    Interval merge_interval;
    if (overlapping_start) {
      merge_interval.start = intervals[start_pos].start;
    } else {
      merge_interval.start = newInterval.start;
    }
    if (overlapping_end) {
      merge_interval.end = intervals[end_pos].end;
      res.push_back(merge_interval);
    } else {
      merge_interval.end = newInterval.end;
      res.push_back(merge_interval);
    }
    for (int i = end_pos + 1; i < n; i++) {
      res.push_back(intervals[i]);
    }
    return res;
  }
};
