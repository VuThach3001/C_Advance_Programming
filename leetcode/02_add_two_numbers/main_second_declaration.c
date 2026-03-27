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

 /* Second declaration */
typedef struct Node
{
    int data;
    struct Node* nextPtr;
} Node_t;

typedef Node_t* ListNode_t;

ListNode_t addTwoNumbers (ListNode_t l1, ListNode_t l2);
ListNode_t createList (int* arr, int size);
void printList (ListNode_t head);
void freeList (ListNode_t head);

int main (void)
{
    /* Example: 342 + 465 = 807
     * l1 = [2, 4, 3]  (represents 342)
     * l2 = [5, 6, 4]  (represents 465)
     * result should be [7, 0, 8] (represents 807) */
    int arr1[] = { 2, 4, 3 };
    int arr2[] = { 5, 6, 4 };

    ListNode_t l1 = createList (arr1, 3);
    ListNode_t l2 = createList (arr2, 3);

    printf ("l1: ");
    printList (l1);
    printf ("l2: ");
    printList (l2);

    ListNode_t result = addTwoNumbers (l1, l2);
    printf ("sum: ");
    printList (result);

    freeList (l1);
    freeList (l2);
    freeList (result);

    return 0;
}

ListNode_t createList (int* arr, int size)
{
    ListNode_t head = NULL;
    ListNode_t tail = NULL;
    for (int i = 0; i < size; i++)
    {
        ListNode_t newNode = (ListNode_t)malloc (sizeof (Node_t));
        newNode->data = arr[i];
        newNode->nextPtr = NULL;
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->nextPtr = newNode;
            tail = newNode;
        }
    }
    return head;
}

void printList (ListNode_t head)
{
    ListNode_t current = head;
    printf ("[");
    while (current != NULL)
    {
        printf ("%d", current->data);
        if (current->nextPtr != NULL)
            printf (", ");
        current = current->nextPtr;
    }
    printf ("]\n");
}

void freeList (ListNode_t head)
{
    while (head != NULL)
    {
        ListNode_t temp = head;
        head = head->nextPtr;
        free (temp);
    }
}

ListNode_t addTwoNumbers (ListNode_t l1, ListNode_t l2)
{
    ListNode_t dummyHead = (ListNode_t)malloc (sizeof (Node_t));
    ListNode_t current = dummyHead;
    int carry = 0;
    while (l1 != NULL || l2 != NULL)
    {
        int x = (l1 != NULL) ? l1->data : 0;
        int y = (l2 != NULL) ? l2->data : 0;
        int sum = carry + x + y;
        carry = sum / 10;

        current->nextPtr = (ListNode_t)malloc (sizeof (Node_t));

        current = current->nextPtr;
        current->data = sum % 10;
        if (l1 != NULL) l1 = l1->nextPtr;
        if (l2 != NULL) l2 = l2->nextPtr;
        // current->nextPtr = NULL;
    }
    if (carry > 0)
    {
        current->nextPtr = (ListNode_t)malloc (sizeof (Node_t));
        current = current->nextPtr;
        current->data = carry;
        current->nextPtr = NULL;
    }

    ListNode_t result = dummyHead->nextPtr;
    free (dummyHead);
    return result;
}