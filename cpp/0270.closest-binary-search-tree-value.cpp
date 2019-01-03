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
  int closestValue(int a, int b, double target) {
    if (std::abs(a - target) < std::abs(b - target)) {
      return a;
    } else {
      return b;
    }
  }
  int closestValue(TreeNode* root, double target) {
    if (root->val > target) {
      if (root->left) {
        return closestValue(root->val, closestValue(root->left, target), target);
      } else {
        return root->val;
      }
    } else {
      if (root->right) {
        return closestValue(root->val, closestValue(root->right, target), target);
      } else {
        return root->val;
      }
    }
  }
};
