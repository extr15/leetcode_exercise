/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
// AC. recursive.
class Solution {
 public:
  void convertTreeToList(Node* root, Node*& first, Node*& last) {
    if (!root) {
      first = last = nullptr;
      return;
    }
    first = root;
    last = root;
    if (!root->left && !root->right) {
      return;
    }
    Node *left_first, *left_last, *right_first, *right_last;
    convertTreeToList(root->left, left_first, left_last);
    convertTreeToList(root->right, right_first, right_last);
    if (left_first) {
      first = left_first;
    }
    if (left_last) {
      left_last->right = root;
      root->left = left_last;
    }
    if (right_first) {
      right_first->left = root;
      root->right = right_first;
    }
    if (right_last) {
      last = right_last;
    }
    return;
  }
  Node* treeToDoublyList(Node* root) {
    if (!root) {
      return nullptr;
    }
    Node *first, *last;
    convertTreeToList(root, first, last);
    last->right = first;
    first->left = last;
    return first;
  }
};

// AC. inorder iterative.
class Solution {
 public:
  Node* treeToDoublyList(Node* root) {
    Node* cur = root;
    Node dummy(-1, nullptr, nullptr);
    Node* prev = &dummy;
    stack<Node*> stk;
    while (cur || !stk.empty()) {
      while (cur) {
        stk.push(cur);
        cur = cur->left;
      }
      cur = stk.top();
      stk.pop();

      prev->right = cur;
      cur->left = prev;
      prev = cur;

      cur = cur->right;
    }
    Node* head = dummy.right;
    if (head) {
      prev->right = head;
      head->left = prev;
    }
    return head;
  }
};
