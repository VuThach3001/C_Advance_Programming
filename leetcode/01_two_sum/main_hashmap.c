/*

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

Approach: Hash map (open addressing, linear probing) — O(n) time, O(n) space.

*/
#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum (int* nums, int numSize, int target, int* returnSize);

int main (void)
{
    int nums[] = { 2, 7, 11, 15 };
    int target = 13;
    int returnSize;

    int* result = twoSum (nums, 4, target, &returnSize);

    for (int i = 0; i < returnSize; i++)
    {
        printf ("%d ", result[i]);
    }
    printf ("\n");

    free (result);

    return 0;
}

/* Hash map entry: key = number value, index = its position in nums (-1 = empty) */
typedef struct
{
    int key;
    int index;
} Entry;

#define MAP_SIZE 20011  /* prime larger than 2 * 10^4 */

static unsigned int hash (int key)
{
    return (unsigned int)(key < 0 ? -key : key) % MAP_SIZE;
}

int* twoSum (int* nums, int numSize, int target, int* returnSize)
{
    /* Stack-allocate the hash map (open addressing, linear probing) */
    Entry map[MAP_SIZE];
    for (int i = 0; i < MAP_SIZE; i++) map[i].index = -1;

    for (int i = 0; i < numSize; i++)
    {
        int complement = target - nums[i];

        /* Look up complement in the map */
        unsigned int slot = hash (complement);
        while (map[slot].index != -1)
        {
            if (map[slot].key == complement)
            {
                int* result = (int*)malloc (2 * sizeof (int));
                result[0] = map[slot].index;
                result[1] = i;
                *returnSize = 2;
                return result;
            }
            slot = (slot + 1) % MAP_SIZE;
        }

        /* Insert nums[i] into the map */
        unsigned int ins = hash (nums[i]);
        while (map[ins].index != -1 && map[ins].key != nums[i])
            ins = (ins + 1) % MAP_SIZE;
        map[ins].key = nums[i];
        map[ins].index = i;
    }

    *returnSize = 0;
    return NULL;
}
