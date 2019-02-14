#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
  constexpr static int kIntMax = std::numeric_limits<int>::max();

 public:
  void dfs(TreeNode* root, int k, int& min_dist_to_leaf, int& dist_to_k, int& min_dist,
           int& leaf_val, int& leaf_res) {
    if (!root) {
      min_dist_to_leaf = std::numeric_limits<int>::max();
      leaf_val = std::numeric_limits<int>::max();
      return;
    }
    if (!root->left && !root->right) {
      min_dist_to_leaf = 0;
      if (root->val == k) {
        dist_to_k = 0;
        min_dist = 0;
        leaf_res = k;
      }
      leaf_val = root->val;
      return;
    }
    int min_dist_to_leaf_left, min_dist_to_leaf_right;
    int dist_to_k_left = -1, dist_to_k_right = -1;
    int leaf_val_left, leaf_val_right;
    dfs(root->left, k, min_dist_to_leaf_left, dist_to_k_left, min_dist, leaf_val_left, leaf_res);
    dfs(root->right, k, min_dist_to_leaf_right, dist_to_k_right, min_dist, leaf_val_right, leaf_res);

    min_dist_to_leaf = min(min_dist_to_leaf_left, min_dist_to_leaf_right) + 1;
    // Don't forget to set `leaf_val` to be used by upper caller.
    if(min_dist_to_leaf_left < min_dist_to_leaf_right) {
      leaf_val = leaf_val_left;
    }
    else {
      leaf_val = leaf_val_right;
    }
    //cout << "root->val: " << root->val << ", min_dist_to_leaf_left: " << min_dist_to_leaf_left << ", min_dist_to_leaf_right: " << min_dist_to_leaf_right << ", dist_to_k_left: " << dist_to_k_left << ", dist_to_k_right: " << dist_to_k_right << ", leaf_val_left: " << leaf_val_left << ", leaf_val_right: " << leaf_val_right << endl;
    //cout << "min_dist: " << min_dist << ", min_dist_to_leaf: " << min_dist_to_leaf << endl;
    if (root->val == k) {
      dist_to_k = 0;
      if (min_dist > min_dist_to_leaf) {
        min_dist = min_dist_to_leaf;
        if (min_dist_to_leaf_left < min_dist_to_leaf_right) {
          leaf_val = leaf_val_left;
        } else {
          leaf_val = leaf_val_right;
        }
        leaf_res = leaf_val;
      }
    } else if (dist_to_k_left >= 0) {
      if (dist_to_k < 0 || dist_to_k > dist_to_k_left + 1) {
        dist_to_k = dist_to_k_left + 1;
        // min_dist_to_leaf_right can be kIntMax if root->right is empty.
        if (min_dist_to_leaf_right != kIntMax && min_dist > dist_to_k + min_dist_to_leaf_right) {
          min_dist = dist_to_k + min_dist_to_leaf_right;
          leaf_val = leaf_val_right;
          leaf_res = leaf_val;
        }
      }
    } else if (dist_to_k_right >= 0) {
      if (dist_to_k < 0 || dist_to_k > dist_to_k_right + 1) {
        dist_to_k = dist_to_k_right + 1;
        if (min_dist_to_leaf_left != kIntMax && min_dist > dist_to_k + min_dist_to_leaf_left) {
          min_dist = dist_to_k + min_dist_to_leaf_left;
          leaf_val = leaf_val_left;
          leaf_res = leaf_val;
        }
      }
    }
  }
  int findClosestLeaf(TreeNode* root, int k) {
    int min_dist = std::numeric_limits<int>::max();
    int dist_to_k = -1;
    int min_dist_to_leaf;
    int leaf_val;
    int leaf_res;
    dfs(root, k, min_dist_to_leaf, dist_to_k, min_dist, leaf_val, leaf_res);
    return leaf_res;
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  //[1,2,3,null,null,4,5,6,null,null,7,8,9,10]
  // 7
  vector<TreeNode*> trees(10 + 1);
  for (int i = 1; i <= 10; i++) {
    trees[i] = new TreeNode(i);
  }
  trees[1]->left = trees[2];
  trees[1]->right = trees[3];
  trees[3]->left = trees[4];
  trees[3]->right = trees[5];
  trees[4]->left = trees[6];
  trees[6]->left = trees[8];
  trees[6]->right = trees[9];
  trees[5]->right = trees[7];
  trees[7]->left = trees[10];
  //int k = 7;
  int k = 4;
  int res = sol.findClosestLeaf(trees[1], k);
  cout << "res: " << res << endl;

  return 0;
}
