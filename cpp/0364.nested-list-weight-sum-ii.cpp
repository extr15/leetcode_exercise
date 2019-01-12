/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
// Wrong understanding.
class Solution {
 public:
  int calcSumAndDepth(vector<NestedInteger>& nestedList, int& sum) {
    int integer_sum = 0;
    int max_depth = 1;
    for (auto& nl : nestedList) {
      if (nl.isInteger()) {
        integer_sum += nl.getInteger();
      } else {
        int depth = calcSumAndDepth(nl.getList(), sum);
        max_depth = max(max_depth, depth);
      }
    }
    sum += integer_sum * max_depth;
    return (max_depth + 1);
  }
  int depthSumInverse(vector<NestedInteger>& nestedList) {
    int sum = 0;
    calcSumAndDepth(nestedList, sum);
    return sum;
  }
};

// AC.
class Solution {
 public:
  void calcSum(vector<NestedInteger>& nestedList, int& sum, int depth) {
    for (auto& nl : nestedList) {
      if (nl.isInteger()) {
        sum += nl.getInteger() * depth;
      } else {
        calcSum(nl.getList(), sum, depth - 1);
      }
    }
    return;
  }
  int calcMaxDepth(vector<NestedInteger>& nestedList) {
    if (nestedList.empty()) {
      return 0;
    }
    int max_depth = 1;
    for (auto& nl : nestedList) {
      if (!nl.isInteger()) {
        int depth = calcMaxDepth(nl.getList());
        max_depth = max(max_depth, depth);
      }
    }
    return (max_depth + 1);
  }
  int depthSumInverse(vector<NestedInteger>& nestedList) {
    int sum = 0;
    int max_depth = calcMaxDepth(nestedList);
    calcSum(nestedList, sum, max_depth - 1);
    return sum;
  }
};
