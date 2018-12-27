class TwoSum {
 public:
  /** Initialize your data structure here. */
  TwoSum() {}

  /** Add the number to an internal data structure.. */
  void add(int number) { num_to_cnt_[number]++; }

  /** Find if there exists any pair of numbers which sum is equal to the value. */
  bool find(int value) {
    for (auto v : num_to_cnt_) {
      int minus_num = value - v.first;
      if (minus_num == v.first) {
        if (v.second > 1) {
          return true;
        }
      } else {
        if (num_to_cnt_.find(minus_num) != num_to_cnt_.end()) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  unordered_map<int, int> num_to_cnt_;
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum obj = new TwoSum();
 * obj.add(number);
 * bool param_2 = obj.find(value);
 */
