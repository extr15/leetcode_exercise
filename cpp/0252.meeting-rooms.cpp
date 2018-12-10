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
  bool canAttendMeetings(vector<Interval>& intervals) {
    const int n = intervals.size();
    if (n < 2) {
      return true;
    }
    std::sort(intervals.begin(), intervals.end(),
              [&](const Interval& a, const Interval& b) { return a.start < b.start; });
    for (int i = 1; i < n; i++) {
      if (intervals[i].start < intervals[i - 1].end) {
        return false;
      }
    }
    return true;
  }
};
