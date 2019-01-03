class Solution {
 public:
  bool verifyPreorder(const vector<int>& a, int first, int last) {
    if (first + 1 == last) {
      return true;
    }
    int i = first + 1;
    while (i < last && a[i] < a[first]) {
      i++;
    }
    int left_tree_last = i;
    while (i < last && a[i] > a[first]) {
      i++;
    }
    if (i != last) {
      return false;
    }
    bool is_preorder = true;
    if (left_tree_last > first + 1) {
      is_preorder &= verifyPreorder(a, first + 1, left_tree_last);
    }
    if (left_tree_last < last) {
      is_preorder &= verifyPreorder(a, left_tree_last, last);
    }
    return is_preorder;
  }
  bool verifyPreorder(vector<int>& preorder) {
    if (preorder.empty()) {
      return true;
    }
    return verifyPreorder(preorder, 0, preorder.size());
  }
};
