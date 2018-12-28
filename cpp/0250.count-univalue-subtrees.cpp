// Failed.
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  struct TreeNodeEqual {
    bool isSameTree(const TreeNode* t1, const TreeNode* t2) {
      if (t1 == nullptr && t2 == nullptr) {
        return true;
      } else if (t1 == nullptr || t2 == nullptr) {
        return false;
      }
      return (t1->val == t2->val && isSameTree(t1->left, t2->left) &&
              isSameTree(t1->right, t2->right));
    }
    bool operator()(const TreeNode& t1, const TreeNode& t2) { return isSameTree(t1.left, t2.left); }
  };

 public:
  typedef unordered_set<TreeNode, std::hash<TreeNode>, TreeNodeEqual> TreeSet;
  TreeSet findUniTree(TreeNode* root, unordered_map<int, TreeSet>& val_to_tree,
                      vector<TreeNode*>& all_tree_node) {
    if (!root) {
      return TreeSet();
    };
    TreeSet sub_tree;
    const int val = root->val;
    TreeNode dummy(-1);
    TreeNode* new_root = new TreeNode(val);
    TreeNode* new_tree = deepCopyTree(new_root, all_tree_node);
    dummy.left = new_tree;
    val_to_tree[val].insert(dummy);
    sub_tree.insert(new_tree);
    all_tree_node.push_back(new_tree);

    TreeSet left_sub_tree = findUniTree(root->left, val_to_tree, all_tree_node);
    TreeSet right_sub_tree = findUniTree(root->right, val_to_tree, all_tree_node);
    for (auto lst : left_sub_tree) {
      new_root->left = lst;
      TreeNode* new_tree = deepCopyTree(new_root, all_tree_node);
      dummy.left = new_tree;
      val_to_tree[val].insert(dummy);
      sub_tree.insert(new_tree);
      all_tree_node.push_back(new_tree);
    }
    new_root->left = nullptr;
    for (auto rst : right_sub_tree) {
      new_root->right = rst;
      TreeNode* new_tree = deepCopyTree(new_root, all_tree_node);
      dummy.left = new_tree;
      val_to_tree[val].insert(dummy);
      sub_tree.insert(new_tree);
      all_tree_node.push_back(new_tree);
    }
    for (auto lst : left_sub_tree) {
      new_root->left = lst;
      for (auto rst : right_sub_tree) {
        new_root->right = rst;
        TreeNode* new_tree = deepCopyTree(new_root, all_tree_node);
        dummy.left = new_tree;
        val_to_tree[val].insert(dummy);
        sub_tree.insert(new_tree);
        all_tree_node.push_back(new_tree);
      }
    }
    delete new_root;
    return sub_tree;

    //      if(root->left && root->left->val == val) {
    //        TreeSet left_sub_tree = findUniTree(root->left, val_to_tree);
    //        for(auto st : left_sub_tree) {
    //          new_root->left = st;
    //          TreeNode * new_tree = deepCopyTree(new_root, all_tree_node);
    //          val_to_tree[val].insert(new_tree);
    //          all_tree_node.push_back(new_tree);
    //        }
    //      }
  }
  void releaseTree(TreeNode* root) {
    // TODO.
  }
  TreeNode* deepCopyTree(TreeNode* root) {
    if (!root) {
      return nullptr;
    }
    TreeNode* node = new TreeNode(root->val);
    node->left = deepCopyTree(root->left);
    node->right = deepCopyTree(root->right);
    return node;
  }
  TreeNode* deepCopyTree(TreeNode* root, vector<TreeNode*>& all_tree_node) {
    TreeNode* new_tree = deepCopyTree(root);
    all_tree_node.push_back(new_tree);
    return new_tree;
  }
  int countUnivalSubtrees(TreeNode* root) {
    // unordered_map<int, unordered_set<TreeNode*, std::hash<TreeNode*>, TreeNodeEqual> >
    // val_to_tree;
    unordered_map<int, TreeSet> val_to_tree;
    // TreeNode * cur = root;
    vector<TreeNode*> all_tree_node;
    findUniTree(root, val_to_tree, all_tree_node);
    int count = 0;
    for (auto t : val_to_tree) {
      count += t.second.size();
    }
    for (auto t : all_tree_node) {
      delete t;
    }
    return count;
  }
};

// AC

// method 1
class Solution {
 public:
  bool isUniTree(TreeNode* root, int val) {
    if (!root) {
      return true;
    }
    return ((root->val == val) && isUniTree(root->left, val) && isUniTree(root->right, val));
  }
  int countUnivalSubtrees(TreeNode* root) {
    int cnt = 0;
    if (!root) {
      return 0;
    }
    if (isUniTree(root, root->val)) {
      cnt++;
    }
    cnt += countUnivalSubtrees(root->left);
    cnt += countUnivalSubtrees(root->right);
    return cnt;
  }
};

// method 2
class Solution {
 public:
  bool isUniTreeGivenVal(TreeNode* root, int val, int& count) {
    if (!root) {
      return true;
    }
    bool is_left_uni = isUniTreeGivenVal(root->left, root->val, count);
    bool is_right_uni = isUniTreeGivenVal(root->right, root->val, count);
    if (!is_left_uni || !is_right_uni) {
      return false;
    }
    count++;
    return (root->val == val);
  }
  int countUnivalSubtrees(TreeNode* root) {
    int count = 0;
    isUniTreeGivenVal(root, -1, count);
    return count;
  }
};

// method 3
class Solution {
 public:
  bool isUniTree(TreeNode* root, int& count) {
    if (!root) {
      return true;
    }
    bool is_left_uni = isUniTree(root->left, count);
    bool is_right_uni = isUniTree(root->right, count);
    if (is_left_uni && is_right_uni) {
      if (root->left != nullptr && root->left->val != root->val) {
        return false;
      }
      if (root->right != nullptr && root->right->val != root->val) {
        return false;
      }
      count++;
      return true;
    }
    return false;
  }
  int countUnivalSubtrees(TreeNode* root) {
    int count = 0;
    isUniTree(root, count);
    return count;
  }
};

