/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/
class Solution {
 public:
  Node* insert(Node* head, int insertVal) {
    if (!head) {
      Node* node = new Node(insertVal, nullptr);
      node->next = node;
      return node;
    }
    if (head->next == head) {
      Node* node = new Node(insertVal, head);
      head->next = node;
      return head;
    }
    Node* cur = head->next;
    Node dummy();
    Node* prev = head;
    while (cur != head) {
      bool insert_here = false;
      if (prev->val <= cur->val) {
        if (prev->val <= insertVal && insertVal <= cur->val) {
          insert_here = true;
        }
      } else {
        if (insertVal <= cur->val || insertVal >= prev->val) {
          insert_here = true;
        }
      }

      if (insert_here) {
        Node* node = new Node(insertVal, cur);
        prev->next = node;
        return head;
      }
      prev = cur;
      cur = cur->next;
    }
    // all value are equal in the original list.
    Node* node = new Node(insertVal, cur);
    prev->next = node;
    return head;
  }
};
