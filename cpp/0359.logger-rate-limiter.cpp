class Logger {
 public:
  /** Initialize your data structure here. */
  Logger() {}

  /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
      If this method returns false, the message will not be printed.
      The timestamp is in seconds granularity. */
  bool shouldPrintMessage(int timestamp, string message) {
    if (msg_to_timestamp_.find(message) == msg_to_timestamp_.end()) {
      msg_to_timestamp_.emplace(message, timestamp);
      return true;
    } else {
      if (timestamp - msg_to_timestamp_[message] >= 10) {
        msg_to_timestamp_[message] = timestamp;
        return true;
      } else {
        return false;
      }
    }
  }

 private:
  unordered_map<string, int> msg_to_timestamp_;
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger obj = new Logger();
 * bool param_1 = obj.shouldPrintMessage(timestamp,message);
 */

