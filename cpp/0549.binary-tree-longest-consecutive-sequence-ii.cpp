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
  void findLongest(TreeNode* root, int parent_val, int& inc_len, int& dec_len, int& max_len) {
    if (!root) {
      inc_len = 0;
      dec_len = 0;
      return;
    }
    bool inc_to_parent = false, dec_to_parent = false;
    if (root->val == parent_val - 1) {
      inc_to_parent = true;
    }
    if (root->val == parent_val + 1) {
      dec_to_parent = true;
    }
    int left_inc_len, left_dec_len;
    int right_inc_len, right_dec_len;
    findLongest(root->left, root->val, left_inc_len, left_dec_len, max_len);
    findLongest(root->right, root->val, right_inc_len, right_dec_len, max_len);
    if (inc_to_parent) {
      inc_len = max(left_inc_len, right_inc_len) + 1;
    } else {
      inc_len = 0;
    }
    if (dec_to_parent) {
      dec_len = max(left_dec_len, right_dec_len) + 1;
    } else {
      dec_len = 0;
    }
    max_len = max(max_len, left_inc_len + 1 + right_dec_len);
    max_len = max(max_len, left_dec_len + 1 + right_inc_len);
  }
  int longestConsecutive(TreeNode* root) {
    int max_len = 0;
    int inc_len = 0, dec_len = 0;
    if (!root) {
      return 0;
    }
    findLongest(root, root->val, inc_len, dec_len, max_len);
    return max_len;
  }
};
