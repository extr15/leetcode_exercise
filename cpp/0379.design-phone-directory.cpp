class PhoneDirectory {
 public:
  /** Initialize your data structure here
      @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
  PhoneDirectory(int maxNumbers) {
    for (int i = 0; i < maxNumbers; i++) {
      available_num.insert(i);
    }
    max_num = maxNumbers;
  }

  /** Provide a number which is not assigned to anyone.
      @return - Return an available number. Return -1 if none is available. */
  int get() {
    if (available_num.empty()) {
      return -1;
    }
    int a = *available_num.begin();
    available_num.erase(a);
    assigned_num.insert(a);
    return a;
  }

  /** Check if a number is available or not. */
  bool check(int number) {
    if (available_num.count(number)) {
      return true;
    } else {
      return false;
    }
  }

  /** Recycle or release a number. */
  void release(int number) {
    assigned_num.erase(number);
    if (number < max_num) {
      available_num.insert(number);
    }
  }

 private:
  set<int> available_num;
  set<int> assigned_num;
  int max_num;
};

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj.get();
 * bool param_2 = obj.check(number);
 * obj.release(number);
 */

