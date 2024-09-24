struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *curr1 = l1;
    ListNode *curr2 = l2;
    ListNode *res = new ListNode();
    ListNode *root = res;

    int a, b, sum, carry = 0;
    while (curr1 != nullptr || curr2 != nullptr) {
      a = curr1 != nullptr ? curr1->val : 0;
      b = curr2 != nullptr ? curr2->val : 0;
      sum = a + b + carry;
      carry = sum / 10;

      curr1 = curr1 != nullptr ? curr1->next : nullptr;
      curr2 = curr2 != nullptr ? curr2->next : nullptr;
      res->next = new ListNode(sum % 10);
      res = res->next;
    }

    if (carry != 0) {
      res->next = new ListNode(carry);
    }

    return root->next;
  }
};
