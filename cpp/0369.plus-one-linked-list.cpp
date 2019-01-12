/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* cur = head;
    while(cur) {
      ListNode* tmp = cur->next;
      cur->next = prev;
      prev = cur;
      cur = tmp;
    }
    return prev;
  }
  ListNode* reverseList2(ListNode* head) {
    if (!head) {
      return nullptr;
    }
    ListNode *prev, *cur, *next;
    prev = head;
    cur = head->next;
    head->next = nullptr;
    while (cur) {
      ListNode* tmp = cur->next;
      cur->next = prev;
      prev = cur;
      cur = tmp;
    }
    return prev;
  }
  ListNode* plusOneLessSignificantFirst(ListNode* head) {
    ListNode* cur = head;
    int c = 1;
    ListNode* prev = head;
    while (cur && c != 0) {
      int sum = cur->val + c;
      cur->val = sum % 10;
      c = sum / 10;
      prev = cur;
      cur = cur->next;
    }
    if (c != 0) {
      ListNode* node = new ListNode(1);
      if (head) {
        prev->next = node;
      } else {
        head = node;
      }
    }
    return head;
  }
  ListNode* plusOne(ListNode* head) {
    ListNode* tail = reverseList(head);
    ListNode* res = plusOneLessSignificantFirst(tail);
    return reverseList(res);
  }
};

