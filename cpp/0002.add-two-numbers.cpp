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
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(-1);
    int c = 0;
    ListNode* cur = &dummy;
    int v1, v2;
    while (l1 != nullptr || l2 != nullptr || c != 0) {
      v1 = (l1 != nullptr) ? l1->val : 0;
      v2 = (l2 != nullptr) ? l2->val : 0;
      int s = v1 + v2 + c;
      ListNode* res = new ListNode(s % 10);
      cur->next = res;
      cur = res;
      c = s / 10;
      if (l1) {
        l1 = l1->next;
      }
      if (l2) {
        l2 = l2->next;
      }
    }
    return dummy.next;
  }
};
