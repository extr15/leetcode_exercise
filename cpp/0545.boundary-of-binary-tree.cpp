/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// AC. recursive.
class Solution {
 public:
  void preOrderRecur(TreeNode* root, bool has_left, vector<int>& res) {
    if (!root) {
      return;
    }
    if (!root->left && !root->right) {
      res.push_back(root->val);
      return;
    }
    if (!has_left) {
      res.push_back(root->val);
    }
    preOrderRecur(root->left, has_left, res);
    bool right_child_has_left = has_left || (root->left != nullptr);
    preOrderRecur(root->right, right_child_has_left, res);
  }
  void postOrderRecur(TreeNode* root, bool has_right, vector<int>& res) {
    if (!root) {
      return;
    }
    if (!root->left && !root->right) {
      res.push_back(root->val);
      return;
    }
    bool left_child_has_right = has_right || (root->right != nullptr);
    postOrderRecur(root->left, left_child_has_right, res);
    postOrderRecur(root->right, has_right, res);
    if (!has_right) {
      res.push_back(root->val);
    }
  }

  vector<int> boundaryOfBinaryTree(TreeNode* root) {
    vector<int> res;
    if (!root) {
      return res;
    }
    res.push_back(root->val);
    preOrderRecur(root->left, false, res);
    postOrderRecur(root->right, false, res);
    return res;
  }
};

// AC. iterative.
class Solution {
 public:
  void preOrderIterative(TreeNode* root, vector<int>& res) {
    if (!root) {
      return;
    }
    stack<pair<TreeNode*, bool>> stk;
    stk.push({root, false});
    while (!stk.empty()) {
      auto cur_state = stk.top();
      stk.pop();
      TreeNode* cur = cur_state.first;
      bool has_left = cur_state.second;
      if (!has_left || (!cur->left && !cur->right)) {
        res.push_back(cur->val);
      }
      if (cur->right) {
        bool has_left_child = (cur->left != nullptr);
        stk.push({cur->right, has_left || has_left_child});
      }
      if (cur->left) {
        stk.push({cur->left, has_left});
      }
    }
  }
  void postOrderIterative(TreeNode* root, vector<int>& res) {
    if (!root) {
      return;
    }
    stack<pair<TreeNode*, bool>> stk;
    stack<TreeNode*> post_stk;
    stk.push({root, false});
    while (!stk.empty()) {
      auto cur_state = stk.top();
      stk.pop();
      TreeNode* cur = cur_state.first;
      bool has_right = cur_state.second;
      if (!has_right || (!cur->left && !cur->right)) {
        post_stk.push(cur);
      }
      if (cur->left) {
        bool has_right_child = (cur->right != nullptr);
        stk.push({cur->left, has_right || has_right_child});
      }
      if (cur->right) {
        stk.push({cur->right, has_right});
      }
    }
    while (!post_stk.empty()) {
      TreeNode* cur = post_stk.top();
      post_stk.pop();
      res.push_back(cur->val);
    }
  }
  vector<int> boundaryOfBinaryTree(TreeNode* root) {
    vector<int> res;
    if (!root) {
      return res;
    }
    res.push_back(root->val);
    preOrderIterative(root->left, res);
    postOrderIterative(root->right, res);
    return res;
  }
};

