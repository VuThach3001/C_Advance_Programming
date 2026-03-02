/*
You are given two non-empty linked lists representing two non-negative integers.
The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.
*/

#include <stdio.h>
#include <stdlib.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

 /* First declaration */
struct ListNode
{
    int val;
    struct ListNode* next;
};

struct ListNode* addTwoNumbers (struct ListNode* l1, struct ListNode* l2);

/* Helper: build a linked list from an array of digits (already in reverse order) */
struct ListNode* createList (int* digits, int size)
{
    /* Dummy head to simplify construction */
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    for (int i = 0; i < size; i++)
    {
        /* Allocate a new node for each digit */
        struct ListNode* node = (struct ListNode*)malloc (sizeof (struct ListNode));
        node->val = digits[i];
        node->next = NULL;

        /* Append to the end of the list */
        tail->next = node;
        tail = node;
    }
    return dummy.next;
}

/* Helper: print all values in a linked list */
void printList (struct ListNode* head)
{
    while (head != NULL)
    {
        printf ("%d", head->val);
        if (head->next != NULL) printf (" -> ");
        head = head->next;
    }
    printf ("\n");
}

/* Helper: free all nodes in a linked list */
void freeList (struct ListNode* head)
{
    while (head != NULL)
    {
        struct ListNode* temp = head;
        head = head->next;
        free (temp);
    }
}

int main (void)
{
    /*
     * Example: 342 + 465 = 807
     * l1 = [2 -> 4 -> 3]  (reverse of 342)
     * l2 = [5 -> 6 -> 4]  (reverse of 465)
     * expected result: [7 -> 0 -> 8]  (reverse of 807)
     */
    int digits1[] = { 2, 4, 3 };
    int digits2[] = { 5, 6, 4 };

    /* Build the two input linked lists */
    struct ListNode* l1 = createList (digits1, 3);
    struct ListNode* l2 = createList (digits2, 3);

    printf ("l1     : ");
    printList (l1);

    printf ("l2     : ");
    printList (l2);

    /* Add the two numbers represented as linked lists */
    struct ListNode* result = addTwoNumbers (l1, l2);

    printf ("result : ");
    printList (result);   /* Expected: 7 -> 0 -> 8 */

    /* Clean up allocated memory */
    freeList (l1);
    freeList (l2);
    freeList (result);

    return 0;
}

struct ListNode* addTwoNumbers (struct ListNode* l1, struct ListNode* l2)
{
    /* Allocate a dummy head node to simplify list construction (its ->next will be the real result) */
    struct ListNode* dummyHead = (struct ListNode*)malloc (sizeof (struct ListNode));

    /* 'current' always points to the last node built so far; start at dummyHead */
    struct ListNode* current = dummyHead;

    /* Stores the carry-over digit (0 or 1) from adding two digits that sum >= 10 */
    int carry = 0;

    /* Keep looping as long as either list still has digits to process */
    while (l1 != NULL || l2 != NULL)
    {
        /* Get the current digit of l1; use 0 if l1 is exhausted */
        int x = (l1 != NULL) ? l1->val : 0;

        /* Get the current digit of l2; use 0 if l2 is exhausted */
        int y = (l2 != NULL) ? l2->val : 0;

        /* Add both digits plus any carry from the previous iteration */
        int sum = carry + x + y;

        /* Carry is 1 if sum >= 10, otherwise 0 */
        carry = sum / 10;

        /* Allocate a new node to hold the current result digit */
        current->next = (struct ListNode*)malloc (sizeof (struct ListNode));

        /* Advance current to the newly created node */
        current = current->next;

        /* Store only the units digit (0-9) in the new node */
        current->val = sum % 10;

        /* The last node of a list is set to NULL to mark the end of the list */
        current->next = NULL;

        /* Advance l1 to its next node if it hasn't been exhausted */
        if (l1 != NULL) l1 = l1->next;

        /* Advance l2 to its next node if it hasn't been exhausted */
        if (l2 != NULL) l2 = l2->next;
    }

    /* If there's a remaining carry after both lists are consumed, append a final node */
    if (carry > 0)
    {
        /* Allocate a new node for the leftover carry digit */
        current->next = (struct ListNode*)malloc (sizeof (struct ListNode));

        /* Advance current to the new carry node */
        current = current->next;

        /* The carry will always be 1 here (max digit sum is 9+9+1=19) */
        current->val = carry;

        /* Mark the end of the result list */
        current->next = NULL;
    }

    /* Skip dummyHead and return the actual first node of the result list */
    return dummyHead->next;
}