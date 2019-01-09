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
  vector<vector<int>> verticalOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) {
      return res;
    }
    unordered_map<TreeNode*, int> node_to_vert_idx;
    queue<TreeNode*> q;
    q.push(root);
    vector<TreeNode*> all_node;
    node_to_vert_idx.emplace(root, 0);
    int min_idx = 0, max_idx = 0;
    while (!q.empty()) {
      int len = q.size();
      for (int i = 0; i < len; i++) {
        TreeNode* cur = q.front();
        q.pop();
        all_node.push_back(cur);
        int idx = node_to_vert_idx[cur];
        if (cur->left) {
          q.push(cur->left);
          node_to_vert_idx.emplace(cur->left, idx - 1);
          min_idx = min(min_idx, idx - 1);
        }
        if (cur->right) {
          q.push(cur->right);
          node_to_vert_idx.emplace(cur->right, idx + 1);
          max_idx = max(max_idx, idx + 1);
        }
      }
    }
    const int idx_cnt = max_idx - min_idx + 1;
    res.resize(idx_cnt, vector<int>());
    for (auto& n : all_node) {
      int idx = node_to_vert_idx[n] - min_idx;
      res[idx].push_back(n->val);
    }
    return res;
  }
};

class Solution {
 public:
  void dfs(TreeNode* root, int height, int col, map<int, map<int, vector<int>>>& col_idx_to_val) {
    if (!root) {
      return;
    }
    col_idx_to_val[col][height].push_back(root->val);
    dfs(root->left, height + 1, col - 1, col_idx_to_val);
    dfs(root->right, height + 1, col + 1, col_idx_to_val);
  }
  vector<vector<int>> verticalOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) {
      return res;
    }
    map<int, map<int, vector<int>>> col_idx_to_val;  // map<col_idx, map<height, vector<node_val>> >.
    dfs(root, 0, 0, col_idx_to_val);
    res.resize(col_idx_to_val.size());
    int idx = 0;
    for (const auto& col : col_idx_to_val) {
      for (auto& height_to_val : col.second) {
        auto& v = height_to_val.second;
        std::copy(v.begin(), v.end(), std::back_inserter(res[idx]));
      }
      idx++;
    }
    return res;
  }
};
