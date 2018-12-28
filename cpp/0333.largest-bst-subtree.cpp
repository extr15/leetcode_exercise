/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Failed. Wrong answer.
class Solution {
 public:
  bool isBST(TreeNode* root, int& max_node_num) {
    if (!root) {
      max_node_num = 0;
      return true;
    }
    int left_max_node_num, right_max_node_num;
    bool left_tree = isBST(root->left, left_max_node_num);
    bool right_tree = isBST(root->right, right_max_node_num);
    max_node_num = max(left_max_node_num, right_max_node_num);
    if (!left_tree || !right_tree) {
      return false;
    }
    if (root->left && root->left->val > root->val) {
      return false;
    }
    if (root->right && root->right->val < root->val) {
      return false;
    }
    max_node_num = left_max_node_num + right_max_node_num + 1;
    return true;
  }
  int largestBSTSubtree(TreeNode* root) {
    int max_node_num;
    isBST(root, max_node_num);
    return max_node_num;
  }
};

class Solution {
 public:
  bool isBST(TreeNode* root, int& max_node_num, int& max_val, int& min_val) {
    if (!root) {
      max_node_num = 0;
      return true;
    }
    int left_max_node_num, right_max_node_num;
    int left_max, left_min, right_max, right_min;
    bool left_tree = isBST(root->left, left_max_node_num, left_max, left_min);
    bool right_tree = isBST(root->right, right_max_node_num, right_max, right_min);
    max_node_num = max(left_max_node_num, right_max_node_num);
    if (!left_tree || !right_tree) {
      return false;
    }
    if (root->left && left_max >= root->val) {
      return false;
    }
    if (root->right && right_min <= root->val) {
      return false;
    }
    max_node_num = left_max_node_num + right_max_node_num + 1;
    max_val = root->val;
    min_val = root->val;
    if (root->left) {
      max_val = max(max_val, left_max);
      min_val = min(min_val, left_min);
    }
    if (root->right) {
      max_val = max(max_val, right_max);
      min_val = min(min_val, right_min);
    }
    return true;
  }
  int largestBSTSubtree(TreeNode* root) {
    int max_node_num;
    int min_val, max_val;
    isBST(root, max_node_num, max_val, min_val);
    return max_node_num;
  }
};

