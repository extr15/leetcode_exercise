/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
 public:
  int calcTreeSum(TreeNode* root, unordered_map<int, int>& sum_to_times) {
    if (!root) {
      return 0;
    }
    int sum =
        root->val + calcTreeSum(root->left, sum_to_times) + calcTreeSum(root->right, sum_to_times);
    sum_to_times[sum]++;
    return sum;
  }
  bool checkEqualTree(TreeNode* root) {
    unordered_map<int, int> sum_to_times;
    //unordered_set<int> sum_set;
    int sum = calcTreeSum(root, sum_to_times);
    if (sum == 0) {
      if (sum_to_times[0] > 1) {
        return true;
      } else {
        return false;
      }
    }
    if (sum % 2 != 0) {
      return false;
    }
    int half_sum = sum / 2;
    if (sum_to_times.find(half_sum) != sum_to_times.end()) {
      return true;
    } else {
      return false;
    }
  }
};

