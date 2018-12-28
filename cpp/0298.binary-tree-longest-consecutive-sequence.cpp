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
  int longestConsecutive(TreeNode* root, int& max_len) {
    if (!root) {
      return 0;
    }
    if (!root->left && !root->right) {
      return 1;
    }
    int left_len = 0, right_len = 0;
    if (root->left) {
      left_len = longestConsecutive(root->left, max_len);
      max_len = std::max(max_len, left_len);
      if (root->val + 1 != root->left->val) {
        left_len = 0;
      }
    }
    if (root->right) {
      right_len = longestConsecutive(root->right, max_len);
      max_len = std::max(max_len, right_len);
      if (root->val + 1 != root->right->val) {
        right_len = 0;
      }
    }

    return (std::max(left_len, right_len) + 1);
  }
  int longestConsecutive(TreeNode* root) {
    int max_len = -1;
    int len = longestConsecutive(root, max_len);
    max_len = max(max_len, len);
    return max_len;
  }
};

// Wrong.
int longestConsecutive(TreeNode* root) {
  if (!root) {
    return 0;
  }
  if (!root->left && !root->right) {
    return 1;
  }
  int left_len = longestConsecutive(root->left);
  int right_len = longestConsecutive(root->right);
  if (root->left && root->val + 1 == root->left->val) {
    left_len++;
  }
  if (root->right && root->val + 1 == root->right->val) {
    right_len++;
  }
  return std::max(left_len, right_len);
}

