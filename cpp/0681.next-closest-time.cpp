class Solution {
 public:
  bool isValidTime(int h, int m) { return h >= 0 && h <= 23 && m >= 0 && m <= 59; }
  inline int calcTime(int h, int m) { return h * 60 + m; }
  string nextClosestTime(string time) {
    unordered_set<int> digit;
    int hour = (time[0] - '0') * 10 + (time[1] - '0');
    int minute = (time[3] - '0') * 10 + (time[4] - '0');
    digit.insert(time[0] - '0');
    digit.insert(time[1] - '0');
    digit.insert(time[3] - '0');
    digit.insert(time[4] - '0');
    int digit_cnt = digit.size();
    vector<vector<int> > gen_time;
    for (auto d : digit) {
      vector<int> tmp;
      tmp.push_back(d);
      gen_time.push_back(tmp);
    }
    for (int i = 1; i < 4; i++) {
      vector<vector<int> > next;
      for (int j = 0; j < gen_time.size(); j++) {
        // auto& tmp = gen_time[j]; -- Wrong to use reference and declare here.
        for (auto d : digit) {
          auto tmp = gen_time[j];
          tmp.push_back(d);
          next.push_back(tmp);
        }
      }
      swap(gen_time, next);
    }
    int cur_time = calcTime(hour, minute);
    int min_delta_time = 24 * 60;
    int res_h = -1, res_m;
    for (auto t : gen_time) {
      int h = t[0] * 10 + t[1];
      int m = t[2] * 10 + t[3];
      if (!isValidTime(h, m) || (h == hour && m == minute)) {
        continue;
      }
      int next_time = calcTime(h, m);
      int delta_time = next_time - cur_time;
      if (delta_time < 0) {
        delta_time += 24 * 60;
      }
      if (delta_time < min_delta_time) {
        min_delta_time = delta_time;
        res_h = h;
        res_m = m;
      }
    }
    // input `time` is "00:00".
    if(res_h < 0) {
      return time;
    }
    string res;
    if (res_h < 10) {
      res += "0";
    }
    res += to_string(res_h);
    res += ":";
    if (res_m < 10) {
      res += "0";
    }
    res += to_string(res_m);
    return res;
  }
};
