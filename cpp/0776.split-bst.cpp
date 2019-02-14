/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// AC. version 1
class Solution {
 public:
  void dfs(TreeNode* root, int v, TreeNode*& left_part, TreeNode*& right_part, TreeNode*& new_root,
           bool check_left) {
    if (!root) {
      return;
    }
    if (root->val == v) {
      if(check_left) {
        new_root = root;
      }
      else {
        new_root = root->right;
      }
      right_part = root->right;
      // set `right` to `nullptr`.
      root->right = nullptr;
      left_part = root;
      return;
    }
    if (root->val < v) {
      TreeNode* left_tmp = nullptr;
      TreeNode* right_tmp = nullptr;
      dfs(root->right, v, left_tmp, right_tmp, new_root, check_left);
      root->right = left_tmp;
      left_part = root;
      right_part = right_tmp;
      if (check_left) {
        new_root = root;
      }
    } else {
      TreeNode* left_tmp = nullptr;
      TreeNode* right_tmp = nullptr;
      dfs(root->left, v, left_tmp, right_tmp, new_root, check_left);
      root->left = right_tmp;
      left_part = left_tmp;
      right_part = root;
      if (!check_left) {
        new_root = root;
      }
    }
  }
  // The output order of OJ test matters, left part should first, then right part.
  void processOutputOrder(vector<TreeNode*>& res, int v) {
    if(res.size() < 2) {
      return;
    }
    TreeNode* n1 = res[0];
    TreeNode* n2 = res[1];
    bool rev = false;
    if (n1 && !n2) {
      if(n1->val > v) {
        rev = true;
      }
    } else if (!n1 && n2) {
      if(n2->val <= v) {
        rev = true;
      }
    } else {
      if (n1->val > n2->val) {
        rev = true;
      }
    }
    if (rev) {
      reverse(res.begin(), res.end());
    }
  }
  vector<TreeNode*> splitBST(TreeNode* root, int v) {
    vector<TreeNode*> res;
    bool check_left;
    if (!root) {
      res.push_back(nullptr);
      res.push_back(nullptr);
      return res;
    }
    if (root->val == v) {
      res.push_back(root);
      res.push_back(root->right);
      root->right = nullptr;
      //processOutputOrder(res);
      return res;
    } else if (root->val < v) {
      check_left = false;
    } else {
      check_left = true;
    }
    // init `new_root` in case of this tree has only one node.
    TreeNode *left_part, *right_part, *new_root = nullptr;
    dfs(root, v, left_part, right_part, new_root, check_left);
    res.push_back(root);
    res.push_back(new_root);
    processOutputOrder(res, v);
    return res;
  }
};

// AC. version 2
class Solution {
 public:
  vector<TreeNode*> splitBST(TreeNode* root, int v) {
    vector<TreeNode*> res(2, nullptr);
    if(!root) {
      return res;
    }
    if(root->val <=v) {
      res = splitBST(root->right, v);
      root->right = res[0];
      res[0] = root;
      return res;
    }
    else {
      res = splitBST(root->left, v);
      root->left = res[1];
      res[1] = root;
      return res;
    }
  }
};
