#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// AC. DFS.
class Solution1 {
 public:
  TreeNode* dfs(const string& s, int start_idx, int end_idx) {
    while (start_idx < end_idx && s[start_idx] == ')') {
      start_idx++;
    }
    if (start_idx >= end_idx) {
      return nullptr;
    }
    // cout << "sub: " << s.substr(start_idx, end_idx-start_idx) << endl;
    int i = start_idx;
    int val = 0;
    bool neg = false;
    if (s[i] == '-') {
      neg = true;
      i++;
    }
    while (i < end_idx && s[i] >= '0' && s[i] <= '9') {
      val = val * 10 + (s[i] - '0');
      i++;
    }
    if (neg) {
      val *= -1;
    }
    TreeNode* node = new TreeNode(val);
    while (i < end_idx && s[i] == ')') {
      i++;
    }
    if (i == end_idx) {
      return node;
    }
    int left_parenthesis_cnt = 0;
    int right_parenthesis_cnt = 0;
    int left_start_idx = i + 1;
    while (i < end_idx) {
      if (s[i] == '(') {
        left_parenthesis_cnt++;
      } else if (s[i] == ')') {
        right_parenthesis_cnt++;
      }
      if (left_parenthesis_cnt == right_parenthesis_cnt) {
        // cout << "left_parenthesis_cnt: " << left_parenthesis_cnt << ", i: " << i << endl;
        break;
      }
      i++;
    }
    // cout << "val: " << val << ", left_start_idx: " << left_start_idx << ", i: " << i << ",
    // end_idx: " << end_idx << endl; cout << "left: " << s.substr(left_start_idx, i-left_start_idx)
    // << ", right: " << s.substr(i+2, end_idx-i-2) << endl;
    node->left = dfs(s, left_start_idx, i);
    //    if(i==end_idx) {
    //      return node;
    //    }
    node->right = dfs(s, i + 2, end_idx);
    return node;
  }
  TreeNode* str2tree(string s) {
    if (s.empty()) {
      return nullptr;
    }
    return dfs(s, 0, s.size());
  }
};

// AC. DFS. version 2.
class Solution2 {
 public:
  TreeNode* dfs(const string& s, int& idx) {
    const int n = s.size();
    while (idx < n && (s[idx] == '(' || s[idx] == ')')) {
      idx++;
    }
    if (idx >= n) {
      return nullptr;
    }
    bool neg = false;
    if (idx < n && s[idx] == '-') {
      idx++;
      neg = true;
    }
    int val = 0;
    while (idx < n && s[idx] >= '0' && s[idx] <= '9') {
      val = val * 10 + (s[idx] - '0');
      idx++;
    }
    if (neg) {
      val *= -1;
    }
    TreeNode* node = new TreeNode(val);
    if (idx == n || s[idx] == ')') {
      idx++;
      return node;
    }
    if (s[idx] == '(') {
      idx++;
      node->left = dfs(s, idx);
    }
    //    while (idx < n && (s[idx] == '(' || s[idx] == ')')) {
    //      idx++;
    //    }
    if (idx < n && s[idx] == '(') {
      node->right = dfs(s, idx);
    }
    if (idx < n && s[idx] == ')') {
      idx++;
    }
    return node;
  }
  TreeNode* str2tree(string s) {
    if (s.empty()) {
      return nullptr;
    }
    int idx = 0;
    return dfs(s, idx);
  }
};

// AC. iterative.
class Solution {
 public:
  TreeNode* str2tree(string s) {
    if (s.empty()) {
      return nullptr;
    }
    const int n = s.size();
    int i = 0;
    bool neg = false;
    int val = 0;
    stack<TreeNode*> stk;
    stack<int> state;
    TreeNode dummy(-1);
    stk.push(&dummy);
    state.push(0);
    bool is_num = false;
    while (i < n) {
      // cout << "i: " << i << ", " << s[i] << endl;
      if (s[i] == '-') {
        neg = true;
        is_num = true;
      } else if (s[i] >= '0' && s[i] <= '9') {
        is_num = true;
        val = val * 10 + (s[i] - '0');
      } else {
        TreeNode* parent = stk.top();
        int& cur_state = state.top();
        if (is_num) {
          is_num = false;
          if (neg) {
            val *= -1;
            neg = false;
          }
          TreeNode* node = new TreeNode(val);
          val = 0;
          if (cur_state == 0) {
            parent->left = node;
            cur_state = 1;
          } else {
            parent->right = node;
          }
          stk.push(node);
          // cout << "push: " << stk.top()->val << endl;
          state.push(0);
        } else {
          cur_state = 1;
        }

        if (s[i] == '(') {
        } else {
          // cout << "pop: " << stk.top()->val << endl;
          stk.pop();
          state.pop();
        }
      }
      i++;
    }
    // handle only one num: "3".
    if (is_num) {
      if (neg) {
        val *= -1;
        neg = false;
      }
      TreeNode* node = new TreeNode(val);
      return node;
    }
    return dummy.left;
  }
};

void printTreeLevelOrder(TreeNode* root) {
  if (!root) {
    return;
  }
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    TreeNode* cur = q.front();
    q.pop();
    cout << cur->val << " ";
    if (cur->left) {
      q.push(cur->left);
    }
    if (cur->right) {
      q.push(cur->right);
    }
  }
  cout << endl;
}

int main(int argc, char* argv[]) {
  Solution sol;
  TreeNode* root = sol.str2tree("4(2(3)(1))(6(5))");
  // "4(2(3))(6(5)(7))"
  printTreeLevelOrder(root);

  return 0;
}
