class MaxStack {
  const static int kIntMin = std::numeric_limits<int>::min();

 public:
  /** initialize your data structure here. */
  MaxStack() { cur_max = kIntMin; }

  void push(int x) {
    cur_max = max(cur_max, x);
    k.push({x, cur_max});
  }

  int pop() {
    int v = k.top().first;
    k.pop();
    if (k.empty()) {
      cur_max = kIntMin;
    } else {
      cur_max = k.top().second;
    }
    return v;
  }

  int top() {
    int v = k.top().first;
    return v;
  }

  int peekMax() { return cur_max; }

  int popMax() {
    stack<int> t;
    int v = k.top().first;
    int old_max = cur_max;
    while (v != cur_max) {
      t.push(v);
      k.pop();
      v = k.top().first;
    }
    pop();  // not k.pop() since we need handle `cur_max`.
    while (!t.empty()) {
      push(t.top());
      t.pop();
    }
    return old_max;
  }

 private:
  stack<pair<int, int>> k;  // pair<val, cur_max>.
  int cur_max;
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack obj = new MaxStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.peekMax();
 * int param_5 = obj.popMax();
 */
