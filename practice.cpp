//
// Created by Guillermo Galvez on 08/01/2025.
//

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        auto temp = head;
        while (temp->next != nullptr){
            if (temp->next->val == val) {
                auto temp2 = temp->next->next;
                temp->next->next= nullptr;
                delete temp->next;
                temp->next = temp2;
            }
            temp = temp->next;
        }
        return head;
    }
};

int main(){
    
}