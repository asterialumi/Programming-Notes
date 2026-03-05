#include <iostream>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* merge(ListNode* left, ListNode* right) {
    ListNode* leftcurr = left;
    ListNode* rightcurr = right;
    ListNode* sorted = nullptr;
    ListNode* sortcurr = nullptr;

    while(leftcurr && rightcurr) {
        if(leftcurr->val <= rightcurr->val) {
            if(!sortcurr) {
                sortcurr = leftcurr;
                sorted = sortcurr;
            }
            else {
                sortcurr->next = leftcurr;
                sortcurr = sortcurr->next;
            }
            leftcurr = leftcurr->next;
        }
        else {
            if(!sortcurr) {
                sortcurr = rightcurr;
                sorted = sortcurr;
            }
            else {
                sortcurr->next = rightcurr;
                sortcurr = sortcurr->next;
            }
            rightcurr = rightcurr->next;
        }
    }

    while(leftcurr) {
        sortcurr->next = leftcurr;
        sortcurr = sortcurr->next;
        leftcurr = leftcurr->next;
    }

    while(rightcurr) {
        sortcurr->next = rightcurr;
        sortcurr = sortcurr->next;
        rightcurr = rightcurr->next;
    }

    return sorted;
}

ListNode* mergeSort(ListNode* head) {
    ListNode *left = head;
    ListNode *curr = head, *mid = left;
    int count = 1, half = 1;

    while(curr) {
        if(count > half * 2) {
            mid = mid->next;
            half++;
        }
        curr = curr->next;
        count++;
    }

    ListNode *right = mid->next;
    mid->next = nullptr;

    if(left->next) left = mergeSort(left);
    if(right->next) right = mergeSort(right);
    return merge(left, right);
}


ListNode* sortList(ListNode* head) {
    if(!head || !head->next) return head;
    return mergeSort(head);
}

//Helpers
void initialize_node(ListNode* head) {
    ListNode* curr = head;

    curr->next = new ListNode(27);
    curr = curr->next;
    curr->next = new ListNode(54);
    curr = curr->next;
    curr->next = new ListNode(12);
    curr = curr->next;
    curr->next = new ListNode(63);
    curr = curr->next;
    curr->next = new ListNode(8);
    curr = curr->next;
    curr->next = new ListNode(120);
    curr = curr->next;
    curr->next = new ListNode(34);
    curr = curr->next;
    curr->next = nullptr;
}

void printList(ListNode* head) {
    ListNode* curr = head;

    while(curr) {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;
}

int main() {
    ListNode* head = new ListNode(38);
    initialize_node(head);

    cout << "BEFORE: ";
    printList(head);

    head = sortList(head);

    cout << "AFTER:  ";
    printList(head);
}