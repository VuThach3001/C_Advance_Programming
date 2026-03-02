/*

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

*/
#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum (int* nums, int numSize, int target, int* returnSize);

int main (void)
{
    /* Type the input that need for the function */
    int nums[] = { 2, 7, 11, 15 };
    int target = 13;
    int returnSize;

    int* result = twoSum (nums, 4, target, &returnSize);

    /*  Print the result */
    for (int i = 0; i < returnSize; i++)
    {
        printf ("%d ", result[i]);
    }
    printf ("\n");

    free (result);

    return 0;
}

int* twoSum (int* nums, int numSize, int target, int* returnSize)
{
    for (int i = 0; i < numSize; i++)
    {
        /* Not use the same element twice */
        for (int j = i + 1; j < numSize; j++)
        {
            if (nums[i] + nums[j] == target)
            {
                /* Malloc memory for the result */
                int* result = (int*)malloc (2 * sizeof (int));
                result[0] = i;
                result[1] = j;
                /* Assign the value to returnSize */
                *returnSize = 2;
                return result;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}
