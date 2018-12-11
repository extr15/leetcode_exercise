// AC, but slow.
class MedianFinder {
 public:
  /** initialize your data structure here. */
  MedianFinder() { len = 0; }

  void addNum(int num) {
    int left = 0, right = len;
    while (left < right) {
      int mid = (left + right) / 2;
      if (val[mid] < num) {
        left = mid + 1;
      } else if (val[mid] > num) {
        right = mid;
      } else {
        left = mid;
        break;
      }
    }
    val.push_back(num);
    len++;
    for (int i = len - 1; i > left; i--) {
      val[i] = val[i - 1];
    }
    val[left] = num;
  }

  double findMedian() {
    int mid = len / 2;
    if (len % 2 == 1) {
      return val[mid];
    } else {
      return (val[mid] + val[mid - 1]) / 2.0;
    }
  }

 private:
  vector<int> val;
  int len;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */

// AC
class MedianFinder {
 public:
  /** initialize your data structure here. */
  MedianFinder() {
    len = 0;
    is_len_odd = false;
    med_int = 0;
    med_int_cnt = 0;
  }

  void addNum(int num) {
    val_to_cnt[num]++;
    len++;
    is_len_odd = !is_len_odd;
    if (len == 1) {
      med_int = num;
      return;
    }
    if (num == med_int) {
      if (is_len_odd) {
        med_int_cnt++;
      }
    } else if (num < med_int) {
      if (!is_len_odd) {
        if (med_int_cnt > 0) {
          med_int_cnt--;
        } else {
          auto it = val_to_cnt.lower_bound(med_int);
          it--;
          med_int = it->first;
          med_int_cnt = it->second - 1;
        }
      }
    } else {
      if (is_len_odd) {
        if (med_int_cnt < val_to_cnt[med_int] - 1) {
          med_int_cnt++;
        } else {
          auto it = val_to_cnt.upper_bound(med_int);
          med_int = it->first;
          med_int_cnt = 0;
        }
      }
    }
  }
  double findMedian() {
    if (is_len_odd) {
      return med_int;
    } else {
      if (val_to_cnt[med_int] > med_int_cnt + 1) {
        return med_int;
      } else {
        auto it = val_to_cnt.upper_bound(med_int);
        return ((double)(med_int + it->first)) / 2.0;
      }
    }
  }

 private:
  int med_int;
  int med_int_cnt;
  map<int, int> val_to_cnt;
  int len;
  bool is_len_odd;
};
