// Not finish.
class MyCalendarTwo {
 public:
  MyCalendarTwo() {}

  bool book(int start, int end) {
    if (book_time.empty()) {
      vector<int> end_time;
      end_time.push_back(end);
      book_time.insert({start, end_time});
      return true;
    }
    auto it1 = book_time.lower_bound(start);
    auto it2 = book_time.upper_bound(end);
    int occupancy_times = 1;
    int next_start = start, next_end = ;
    for(auto it = it1; it != it2;) {
      auto& end_time = it->second;
      for(auto e: end_time) {
      if(e <= start) {
        occupancy_times--;
      }
      }
      if(it->start <= end) {
        occupancy_times += end_time.size();
      }
      if(occupancy_times > 2) {
        return false;
      }
    }
    if(book_time.find(start) != book_time.end()) {
      auto& end_time = book_time[start];
      end_time.push_back(end);
    }
    else {
      vector<int> end_time;
      end_time.push_back(end);
      book_time.insert({start, end_time});
    }
    return true;
  }

 private:
  std::map<int, vector<int>> book_time;
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo obj = new MyCalendarTwo();
 * bool param_1 = obj.book(start,end);
 */

// AC
class MyCalendarTwo {
 public:
  MyCalendarTwo() {}

  bool book(int start, int end) {
    if (time_to_start_end_cnt.size() <2) {
      time_to_start_end_cnt[start].first++;
      time_to_start_end_cnt[end].second++;
      return true;
    }
    int occupancy_times = 0;
    bool not_start = true;
    auto it = time_to_start_end_cnt.begin();
    if(start < it->first) {
      occupancy_times++;
    }
    if(end <= it->first) {
      occupancy_times--;
      time_to_start_end_cnt[start].first++;
      time_to_start_end_cnt[end].second++;
      return true;
    }
    auto prev_it = it;
    it++;
    while(it != time_to_start_end_cnt.end()) {
      
      auto& start_end_cnt = prev_it->second;
      if(start_end_cnt.first > 0) {
        occupancy_times += start_end_cnt.first; 
      }
      if(start_end_cnt.second > 0) {
        occupancy_times -= start_end_cnt.second; 
      }
      if(start >=prev_it->first && start < it->first) {
        occupancy_times++;
      }
      if(occupancy_times >2) {
        return false;
      }
      if(end > prev_it->first && end <= it->first) {
        occupancy_times--;
        break;
      }
      prev_it = it;
      it++;
    }
    time_to_start_end_cnt[start].first++;
    time_to_start_end_cnt[end].second++;
    return true;
    /* 
    auto it1 = time_to_start_end_cnt.lower_bound(start);
    auto it2 = time_to_start_end_cnt.upper_bound(end);
    if(it1 == time_to_start_end_cnt.end() || it2 == time_to_start_end_cnt.begin()) {
      time_to_start_end_cnt[start].first++;
      time_to_start_end_cnt[end].second++;
      return true;
    }

    int occupancy_times = 0;
    int start_times = 0, end_times = 0;
    if(it1 != time_to_start_end_cnt.begin()) {
      it1--;
      start_times += it1->second.first;
      end_times += it1->second.second;
      if(it1 != time_to_start_end_cnt.begin()) {
        it1--;
        start_times += it1->second.first;
        end_times += it1->second.second;
      }
    }
    bool init = true;
    for(auto it = it1; it != it2; ) {
      auto& start_end_cnt = it.second;
      if(start_end_cnt.first)

    } */
  }
 private:
    map<int, std::pair<int, int>> time_to_start_end_cnt; // map<time, pair<as_start_cnt, as_end_cnt>>;
};
