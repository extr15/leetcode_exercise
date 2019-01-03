/*
// Definition for a Node.
class Node {
public:
    int val = NULL;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
 public:
  TreeNode* encodeDFS(Node* root, TreeNode*& last) {
    if (!root) {
      return nullptr;
    }
    TreeNode* res = new TreeNode(root->val);
    TreeNode* left = new TreeNode(root->children.size());
    res->left = left;
    if (last) {
      last->right = res;
    }
    last = res;
    for (auto& c : root->children) {
      TreeNode* next = last;
      encodeDFS(c, next);
      last = next;
    }
    return res;
  }
  Node* decodeDFS(TreeNode* root, TreeNode*& next) {
    if (!root) {
      return nullptr;
    }
    Node* res = new Node(root->val);
    int child_cnt = root->left->val;
    if (child_cnt == 0) {
      next = root->right;
      return res;
    }
    res->children.resize(child_cnt);
    TreeNode* cur = root->right;
    for (int i = 0; i < child_cnt; i++) {
      res->children[i] = decodeDFS(cur, next);
      cur = next;
    }
    return res;
  }
  // Encodes an n-ary tree to a binary tree.
  TreeNode* encode(Node* root) {
    TreeNode* last = nullptr;
    TreeNode* res = encodeDFS(root, last);
    return res;
  }

  // Decodes your binary tree to an n-ary tree.
  Node* decode(TreeNode* root) {
    TreeNode* next;
    return decodeDFS(root, next);
  }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(root));
