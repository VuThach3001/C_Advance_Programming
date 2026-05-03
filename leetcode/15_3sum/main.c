#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * 3Sum — optimal approach (sorting + two pointers)
 *
 * Technique:
 * 1. Sort the array so duplicates are adjacent and two-pointer scanning works.
 * 2. Fix the first element at index `i`. For the remaining array use two
 *    pointers `l` and `r` to find pairs whose sum equals -nums[i].
 * 3. When a valid pair is found, record the triplet and advance pointers past
 *    duplicate values to avoid repeated triplets.
 *
 * Time complexity: O(n^2). Space: O(m) for output storage.
 */

static int cmp_int(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

int **threeSum(int *nums, int numsSize, int *returnSize,
               int **returnColumnSizes)
{
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (numsSize < 3)
        return NULL;

    /* Sort input to enable two-pointer scanning and duplicate skipping */
    qsort(nums, numsSize, sizeof(int), cmp_int);

    int cap = 16;
    int **res = malloc(cap * sizeof(int *));
    int *colSizes = malloc(cap * sizeof(int));

    /* Fix the first element of the triplet at index i */
    for (int i = 0; i < numsSize - 2; ++i)
    {
        /* Skip duplicate first elements to ensure unique triplets */
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        /* two-pointer window in the subarray (i+1 .. numsSize-1) */
        int l = i + 1, r = numsSize - 1;
        while (l < r)
        {
            long sum = (long)nums[i] + nums[l] + nums[r];
            if (sum == 0)
            {
                if (*returnSize >= cap)
                {
                    cap *= 2;
                    res = realloc(res, cap * sizeof(int *));
                    colSizes = realloc(colSizes, cap * sizeof(int));
                }
                int *trip = malloc(3 * sizeof(int));
                trip[0] = nums[i];
                trip[1] = nums[l];
                trip[2] = nums[r];
                res[*returnSize] = trip;
                colSizes[*returnSize] = 3;
                (*returnSize)++;
                /* advance l and r past duplicates to avoid same triplet */
                int lv = nums[l], rv = nums[r];
                while (l < r && nums[l] == lv)
                    l++;
                while (l < r && nums[r] == rv)
                    r--;
            }
            else if (sum < 0)
            {
                /* sum too small -> move left pointer right to increase sum */
                l++;
            }
            else
            {
                /* sum too large -> move right pointer left to decrease sum */
                r--;
            }
        }
    }

    if (*returnSize == 0)
    {
        free(res);
        free(colSizes);
        *returnColumnSizes = NULL;
        return NULL;
    }

    res = realloc(res, (*returnSize) * sizeof(int *));
    colSizes = realloc(colSizes, (*returnSize) * sizeof(int));
    *returnColumnSizes = colSizes;
    return res;
}

static void print_triplets(int *nums, int numsSize)
{
    /* Helper: copy input (since threeSum sorts in-place) and print results */
    int *copy = malloc(numsSize * sizeof(int));
    memcpy(copy, nums, numsSize * sizeof(int));
    int returnSize = 0;
    int *colSizes = NULL;
    int **res = threeSum(copy, numsSize, &returnSize, &colSizes);

    printf("Input: [");
    for (int i = 0; i < numsSize; ++i)
    {
        printf("%d", nums[i]);
        if (i + 1 < numsSize)
            printf(", ");
    }
    printf("]\n");

    if (returnSize == 0 || res == NULL)
    {
        printf("Output: [] (no triplets)\n\n");
        free(copy);
        return;
    }

    printf("Output (%d triplet(s)):\n", returnSize);
    for (int i = 0; i < returnSize; ++i)
    {
        int *t = res[i];
        printf("  [%d, %d, %d]\n", t[0], t[1], t[2]);
        free(t);
    }
    free(res);
    free(colSizes);
    free(copy);
    printf("\n");
}

int main(void)
{
    /* Some test inputs */
    int a1[] = {-1, 0, 1, 2, -1, -4};
    int a2[] = {0, 0, 0, 0};
    int a3[] = {1, 2, -2, -1};
    int a4[] = {};
    int a5[] = {-2, 0, 1, 1, 2};

    /* Run the helper to print triplets for each test */
    print_triplets(a1, sizeof(a1) / sizeof(a1[0]));
    print_triplets(a2, sizeof(a2) / sizeof(a2[0]));
    print_triplets(a3, sizeof(a3) / sizeof(a3[0]));
    print_triplets(a4, 0);
    print_triplets(a5, sizeof(a5) / sizeof(a5[0]));

    return 0;
}