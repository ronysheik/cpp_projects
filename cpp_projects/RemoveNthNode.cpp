/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
 // function remove Nth node from the end of List
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* temp = NULL;
        ListNode* cur = NULL;
        cur =  temp = dummy;
        if(head->next == NULL || head == NULL)
            return NULL;
        
        for(int i =1; i<=n; i++)
        {
            temp = temp->next;
        }
        
        while(temp->next != NULL)
        {
            temp = temp->next;
            cur = cur->next;
        }
        cur->next = cur->next->next;
        return dummy->next;
    }
};