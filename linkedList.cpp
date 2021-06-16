#include<iostream>

using namespace std;

class ListNode{
public:
    int val = 0;
    ListNode* next = nullptr;

    ListNode(int val){
        this->val = val;
    }
};

// 876. Middle of the Linked List
ListNode* middleNode(ListNode* head) {
    if(head == nullptr) return head;
    ListNode* fast = head;
    ListNode* slow = head;

    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode* midNode(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* fast = head;
    ListNode* slow = head;

    while(fast->next != nullptr && fast->next->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 206. Reverse Linked List
ListNode* reverseList(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;

    ListNode* curr = head;
    ListNode* prev = nullptr;

    while(curr != nullptr){
        ListNode* forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    } 
    return prev;
}

// 234. Palindrome Linked List
// 1. find mid. 2. break link and separate the ll.
// 3. 2nd ll ko reverse krdo.
// 4. compare dono list ko

bool isPalindrome(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return true;

    ListNode* mid = midNode(head);
    ListNode* nHead = mid->next;

    mid->next = nullptr;

    nHead = reverseList(nHead);

    ListNode* c1 = head;
    ListNode* c2 = nHead;

    while(c2 != nullptr){
        ListNode* f1 = c1->next;
        ListNode* f2 = c2->next;

        if(c1->val != c2->val) return false;

        c1 = f1;
        c2 = f2;
    }

    return true;
}

int main(){
    return 0;
}

