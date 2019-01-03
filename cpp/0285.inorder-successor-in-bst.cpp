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
  TreeNode* inorder(TreeNode* root, TreeNode* parent, TreeNode* p) {
    if (!root) {
      return nullptr;
    }
    TreeNode* ret = inorder(root->left, root, p);
    if (ret) {
      return ret;
    }
    if (root == p) {
      if (!root->right) {
        return parent;
      }
      TreeNode* next = root->right;
      while (next->left) {
        next = next->left;
      }
      return next;
    }
    return inorder(root->right, parent, p);
  }
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) { return inorder(root, nullptr, p); }
};

class Solution {
 public:
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    if (!root || !p) {
      return nullptr;
    }
    stack<TreeNode*> stk;
    stk.push(root);
    while (root->left) {
      root = root->left;
      stk.push(root);
    }
    while (!stk.empty()) {
      TreeNode* cur = stk.top();
      stk.pop();
      if (cur->right) {
        TreeNode* tmp = cur->right;
        stk.push(tmp);
        while (tmp->left) {
          tmp = tmp->left;
          stk.push(tmp);
        }
      }
      if (cur == p) {
        if (stk.empty()) {
          return nullptr;
        } else {
          return stk.top();
        }
      }
    }
    return nullptr;
  }
};

