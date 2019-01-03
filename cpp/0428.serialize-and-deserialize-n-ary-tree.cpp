#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Definition for a Node.
class Node {
 public:
  int val = NULL;
  vector<Node*> children;

  Node() {}

  Node(int _val, vector<Node*> _children = vector<Node*>()) {
    val = _val;
    children = _children;
  }
};

class Codec {
 public:
  string serializeBFS(Node* root) {
    string res;
    if (!root) {
      return res;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
      int len = q.size();
      for (int i = 0; i < len; i++) {
        Node* cur = q.front();
        q.pop();
        if (!cur) {
          res += "v";
          continue;
        }
        auto& child = cur->children;
        res += ("v" + std::to_string(cur->val) + "c" + std::to_string(child.size()));
        for (auto& c : child) {
          q.push(c);
        }
      }
    }
    return res;
  }
  Node* deserializeBFS(const string& s) {
    if (s.empty()) {
      return nullptr;
    }
    const int n = s.size();
    int i = 0;
    queue<Node*> q;
    Node dummy;
    Node* father = &dummy;
    dummy.children.resize(1);
    int child_idx = 0;
    while (i < n) {
      if (s[i] == 'v') {
        i++;
        Node* node;
        if (s[i] == 'v') {
          node = nullptr;
        } else {
          int val = 0;
          while (s[i] != 'c') {
            val = val * 10 + (s[i] - '0');
            i++;
          }
          i++;
          int child_cnt = 0;
          while (i < n && s[i] != 'v') {
            child_cnt = child_cnt * 10 + (s[i] - '0');
            i++;
          }
          node = new Node();
          node->val = val;
          if (child_cnt > 0) {
            node->children.resize(child_cnt);
            q.push(node);
          }
        }

        if (child_idx < father->children.size()) {
          father->children[child_idx] = node;
          child_idx++;
        } else {
          father = q.front();
          q.pop();
          father->children[0] = node;
          child_idx = 1;
        }
      }
    }
    return dummy.children[0];
  }

  // Encodes a tree to a single string.
  string serialize(Node* root) {
    string res = serializeBFS(root);
    return res;
  }

  // Decodes your encoded data to tree.
  Node* deserialize(string data) { return deserializeBFS(data); }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

string convertTreeToString(Node* root) {
  string res;
  if (!root) {
    return res;
  }
  res += "[" + std::to_string(root->val) + ":";
  for (auto& c : root->children) {
    if (c) {
      res += convertTreeToString(c) + ", ";
    }
  }
  res += "]";
  return res;
}

int main(int argc, char* argv[]) {
  Codec codec;
  Node* l0n0 = new Node(3);
  Node* l1n0 = new Node(1);
  Node* l2n0 = new Node(5);
  l0n0->children.push_back(l1n0);
  l1n0->children.push_back(l2n0);
  string res = codec.serialize(l0n0);
  cout << "res: " << res << endl;
  Node* restore = codec.deserialize(res);
  cout << convertTreeToString(restore) << endl;

  return 0;
}
