class ZigzagIterator {
 public:
  ZigzagIterator(vector<int>& v1, vector<int>& v2) {
    if (!v1.empty()) {
      vec_data_.push_back(v1);
    }
    if (!v2.empty()) {
      vec_data_.push_back(v2);
    }
    vec_idx_ = 0;
    val_idx_ = 0;
  }

  int next() { return vec_data_[vec_idx_++][val_idx_]; }

  bool hasNext() {
    if(vec_data_.empty()) {
      return false;
    }
    if (vec_idx_ == vec_data_.size()) {
      val_idx_++;
      vec_idx_ = 0;
    }
    if(val_idx_ >= vec_data_[vec_idx_].size()) {
      const int n = vec_data_.size();
      int next_vec_idx = vec_idx_;
      while(val_idx_ >= vec_data_[next_vec_idx].size()) {
        next_vec_idx++;
        if(next_vec_idx == n) {
          next_vec_idx = 0;
          val_idx_++;
        }
        if(next_vec_idx == vec_idx_) {
          return false;
        }
      }
      vec_idx_ = next_vec_idx;
    }
    return true;
  }

 private:
  int vec_idx_;
  int val_idx_;
  vector<vector<int>> vec_data_;
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */
