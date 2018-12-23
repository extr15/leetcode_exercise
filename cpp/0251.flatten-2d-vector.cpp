class Vector2D {
 public:
  Vector2D(vector<vector<int>>& vec2d) {
    for (auto v : vec2d) {
      std::copy(v.begin(), v.end(), std::back_inserter(data_));
    }
    idx_ = 0;
  }

  int next() { return data_[idx_++]; }

  bool hasNext() { return idx_ < data_.size(); }

 private:
  vector<int> data_;
  int idx_;
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */

class Vector2D {
 public:
  Vector2D(vector<vector<int>>& vec2d) {
    data_ = vec2d;
    it1_ = data_.begin();
    if(it1_ != data_.end()) {
      it2_ = it1_->begin();
    }
  }
  int next() {
    return *it2_++;
  }
  bool hasNext() {
    if(it1_ == data_.end()) {
      return false;
    }
    while(it1_ != data_.end() && it2_ == it1_->end()) {
          it1_++;
          it2_ = it1_->begin();
    }
    return (it1_ != data_.end());
  }
 private:
  vector<vector<int>> data_;
  vector<vector<int>>::iterator it1_;
  vector<int>::iterator it2_;
};

