class HitCounter {
 public:
  /** Initialize your data structure here. */
  HitCounter() {}

  /** Record a hit.
      @param timestamp - The current timestamp (in seconds granularity). */
  void hit(int timestamp) { hit_.push(timestamp); }

  /** Return the number of hits in the past 5 minutes.
      @param timestamp - The current timestamp (in seconds granularity). */
  int getHits(int timestamp) {
    while (!hit_.empty()) {
      int cur = hit_.front();
      if (timestamp >= cur + 300) {
        hit_.pop();
      } else {
        break;
      }
    }
    return hit_.size();
  }

 private:
  queue<int> hit_;
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter obj = new HitCounter();
 * obj.hit(timestamp);
 * int param_2 = obj.getHits(timestamp);
 */
