/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
 // method takes two linked list and add their elements and return a new linke list
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        ListNode* temp = NULL;
        ListNode* head = NULL;
        ListNode* cur = NULL;
        int carry = 0;
        
        
        while(l1 != NULL || l2 != NULL)
        {
            temp = new ListNode(0);
            temp->val = l1->val + l2->val + carry;
            carry = 0;
            l1 = l1->next;
            l2 = l2->next;
           
            if(temp->val >= 10) {
                carry = temp->val/10;
                temp->val = temp->val%10;       
            }
            
            if(head == NULL) {
                head = temp;
                cur = head;
            }
            else {
                cur->next = temp;
                cur = temp;
            }
            
        }
        if(carry == 1)
        {
            temp = new ListNode(1);
            cur->next = temp;
            cur = temp;
        }
        return head;
    }
    
};

/* test case
Your input:
[2,4,3]
[5,6,4]
Output
[7,0,8]
Expected
[7,0,8]
*/