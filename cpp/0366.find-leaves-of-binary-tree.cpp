/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// AC.
class Solution {
 public:
  int findDepthAndLeaves(TreeNode* root, vector<vector<int>>& res) {
    if (!root) {
      return 0;
    }
    int max_depth = 1;
    if (!root->left && !root->right) {
      if (res.size() < 1) {
        res.push_back(vector<int>());
      }
      res[0].push_back(root->val);
      return 1;
    }
    if (root->left) {
      int depth = findDepthAndLeaves(root->left, res) + 1;
      max_depth = max(max_depth, depth);
    }
    if (root->right) {
      int depth = findDepthAndLeaves(root->right, res) + 1;
      max_depth = max(max_depth, depth);
    }
    if (res.size() < max_depth) {
      res.push_back(vector<int>());
    }
    res[max_depth - 1].push_back(root->val);
    return max_depth;
  }
  vector<vector<int>> findLeaves(TreeNode* root) {
    vector<vector<int>> res;
    findDepthAndLeaves(root, res);
    return res;
  }
};

// AC.
class Solution {
 public:
  int findDepthAndLeaves(TreeNode* root, vector<vector<int>>& res) {
    if (!root) {
      return 0;
    }
    int max_depth = 1;
    int depth_left = findDepthAndLeaves(root->left, res) + 1;
    max_depth = max(max_depth, depth_left);
    int depth_right = findDepthAndLeaves(root->right, res) + 1;
    max_depth = max(max_depth, depth_right);
    if (res.size() < max_depth) {
      res.push_back(vector<int>());
    }
    res[max_depth - 1].push_back(root->val);
    return max_depth;
  }
  vector<vector<int>> findLeaves(TreeNode* root) {
    vector<vector<int>> res;
    findDepthAndLeaves(root, res);
    return res;
  }
};
