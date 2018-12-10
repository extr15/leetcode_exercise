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
  int minMeetingRooms(vector<Interval>& intervals) {
    const int n = intervals.size();
    if (n < 2) {
      return n;
    }
    std::sort(intervals.begin(), intervals.end(),
              [&](const Interval& a, const Interval& b) { return a.start < b.start; });
    std::set<int> end_time;
    int max_room = 0;
    int cur_room = 0;
    for (int i = 0; i < n; i++) {
      if (!end_time.empty()) {
        for (auto it = end_time.begin(); it != end_time.end();) {
          if (intervals[i].start >= *it) {
            it = end_time.erase(it);
            cur_room--;
          } else {
            break;
          }
        }
      }
      end_time.insert(intervals[i].end);
      cur_room++;
      max_room = (max_room > cur_room) ? max_room : cur_room;
    }
    return max_room;
  }
};
