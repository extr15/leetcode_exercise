#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

static const int kIntMax = std::numeric_limits<int>::max();

TreeNode* buildTreeFromSequence(const vector<int>& seq) {
  if (seq.empty() || seq[0] == kIntMax) {
    return nullptr;
  }
  TreeNode* root = new TreeNode(seq[0]);
  queue<TreeNode*> q;
  q.push(root);
  int i = 1;
  const int n = seq.size();
  bool is_left = true;
  while (!q.empty() && i < n) {
    TreeNode* cur = q.front();
    if (seq[i] != kIntMax) {
      TreeNode* node = new TreeNode(seq[i]);
      q.push(node);
      if (is_left) {
        cur->left = node;
      } else {
        cur->right = node;
      }
    }
    i++;
    is_left = !is_left;
    if (is_left) {
      q.pop();
    }
  }
  return root;
}

void treeToSequence(TreeNode* root, vector<int>& seq) {
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    TreeNode* cur = q.front();
    q.pop();
    if (cur == nullptr) {
      seq.push_back(kIntMax);
    } else {
      seq.push_back(cur->val);
      q.push(cur->left);
      q.push(cur->right);
    }
  }
}

void printTree(TreeNode* root) {
  vector<int> out;
  treeToSequence(root, out);
  for (auto v : out) {
    if (v != kIntMax) {
      cout << v << " ";
    } else {
      cout << "# ";
    }
  }
  cout << endl;
}

class Solution {
 public:
  void setRightToParent(TreeNode* root) {
    if (!root || !root->left) {
      return;
    }
    TreeNode* left = root->left;
    TreeNode* right = root->right;
    if (right && !right->right) {
      right->right = root;
    }
    if (left->right) {
      left->right->right = root;
    } else {
      left->right = root;
    }
    setRightToParent(left);
  }
  TreeNode* buildFromDown(TreeNode* cur) {
    if (!cur) {
      return cur;
    }
    if (!cur->right) {
      cur->left = nullptr;
      return cur;
    }
    TreeNode* parent;
    if (cur->right->left == nullptr) {
      parent = cur->right->right;
      cur->right->right = nullptr;
      if (parent == cur) {
        cur->left = nullptr;
        cur->right = nullptr;
        return cur;
      }
    } else {
      parent = cur->right;
    }

    if (!parent->right || parent->right->left != nullptr) {
      cur->left = nullptr;
      cur->right = buildFromDown(parent);
    } else {
      cur->left = parent->right;
      cur->right = buildFromDown(parent);
    }
    return cur;
  }
  TreeNode* upsideDownBinaryTree(TreeNode* root) {
    if (!root) {
      return nullptr;
    }
    setRightToParent(root);
    TreeNode* left = root;
    while (left->left) {
      left = left->left;
    }
    return buildFromDown(left);
  }
};

class Solution {
 public:
  TreeNode* upsideDownBinaryTree(TreeNode* root) {
    if (!root) {
      return nullptr;
    }
    TreeNode* cur, *next_left, *next_right, *parent, *parent_right;
    cur = root;
    parent = parent_right = nullptr;
    while(cur) {
      next_left = cur->left;
      next_right = cur->right;
      cur->left = parent_right;
      cur->right = parent;
      parent = cur;
      parent_right = next_right;
      cur = next_left;
    }
    return parent;
  }
};

int main(int argc, char* argv[]) {
  vector<int> seq{1, 2, 3, 4, 5};
  // vector<int> seq{1, 2};
  TreeNode* root = buildTreeFromSequence(seq);
  Solution sol;
  TreeNode* down_tree = sol.upsideDownBinaryTree(root);
  cout << "output seq: ";
  printTree(down_tree);
  return 0;
}

