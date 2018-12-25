class MovingAverage {
 public:
  /** Initialize your data structure here. */
  MovingAverage(int size) { len_ = size; }

  double next(int val) {
    if (len_ == 0) {
      return 0;
    }
    data_.push_back(val);
    if (data_.size() > len_) {
      data_.pop_front();
    }
    int sum = 0;
    for (auto d : data_) {
      sum += d;
    }
    return (double)sum / data_.size();
  }

 private:
  deque<int> data_;
  int len_;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */
