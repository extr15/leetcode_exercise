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
  void calcDist(TreeNode* root, double target, int k,
                priority_queue<pair<double, int>>& dist_and_val, double& max_dist) {
    if (!root) {
      return;
    }
    double cur_dist = std::abs(target - root->val);
    dist_and_val.push(pair<double, int>(cur_dist, root->val));
    max_dist = max(max_dist, cur_dist);
    if (root->val > target) {
      calcDist(root->left, target, k, dist_and_val, max_dist);
      if (dist_and_val.size() < k || max_dist > cur_dist) {
        calcDist(root->right, target, k, dist_and_val, max_dist);
      }
    } else {
      calcDist(root->right, target, k, dist_and_val, max_dist);
      if (dist_and_val.size() < k || max_dist > cur_dist) {
        calcDist(root->left, target, k, dist_and_val, max_dist);
      }
    }
  }
  vector<int> closestKValues(TreeNode* root, double target, int k) {
    priority_queue<pair<double, int>> dist_and_val;
    double max_dist = -1;
    calcDist(root, target, k, dist_and_val, max_dist);
    vector<int> res;
    const int total = dist_and_val.size();
    for (int i = 0; i < total; i++) {
      if (i >= total - k) {
        res.push_back(dist_and_val.top().second);
      }
      dist_and_val.pop();
    }
    std::reverse(res.begin(), res.end());
    return res;
  }
};
