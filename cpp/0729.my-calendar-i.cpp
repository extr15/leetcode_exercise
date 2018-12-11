class MyCalendar {
 public:
  MyCalendar() {}

  bool book(int start, int end) {
    if (book_time.empty()) {
      book_time.insert({start, end});
      return true;
    }
    bool time_conflict = true;
    auto it = book_time.lower_bound(start);
    if (it == book_time.end()) {
      it--;
      if (it->second > start) {
        return false;
      } else {
        time_conflict = false;
      }
    } else if (it == book_time.begin()) {
      if (end <= it->first) {
        time_conflict = false;
      } else {
        return false;
      }
    } else {
      int next_start = it->first;
      it--;
      if (it->second <= start && next_start >= end) {
        time_conflict = false;
      } else {
        return false;
      }
    }
    if (!time_conflict) {
      book_time.insert({start, end});
      return true;
    } else {
      return false;
    }
  }

 private:
  std::map<int, int> book_time;
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar obj = new MyCalendar();
 * bool param_1 = obj.book(start,end);
 */
