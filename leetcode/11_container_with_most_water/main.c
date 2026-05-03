#include <stdio.h>
#include <stdlib.h>

int maxArea(int *height, int heightSize)
{
    int left = 0;
    int right = heightSize - 1;
    int max = 0;

    while (left < right)
    {
        int h = height[left] < height[right] ? height[left] : height[right];
        int area = h * (right - left);
        if (area > max)
            max = area;

        if (height[left] < height[right])
        {
            left++;
        }
        else
        {
            right--;
        }
    }

    return max;
}

struct TestCase
{
    const char *name;
    int *arr;
    int size;
    int expected;
};

int main(void)
{
    static int t1[] = {1, 8, 6, 2, 5, 4, 8, 3, 7}; // expected 49
    static int t2[] = {1, 1};                      // expected 1
    static int t3[] = {4, 3, 2, 1, 4};             // expected 16
    static int t4[] = {1, 2, 1};                   // expected 2
    static int t5[] = {1, 2, 3, 4, 5};             // expected 6
    static int t6[] = {0, 0, 0};                   // expected 0
    static int t7[] = {5};                         // expected 0
    static int t8[] = {2, 3, 10, 5, 7, 8, 9};      // expected 36

    struct TestCase tests[] = {
        {"example", t1, sizeof(t1) / sizeof(t1[0]), 49},
        {"two_equal", t2, sizeof(t2) / sizeof(t2[0]), 1},
        {"symmetrical", t3, sizeof(t3) / sizeof(t3[0]), 16},
        {"small_peak", t4, sizeof(t4) / sizeof(t4[0]), 2},
        {"increasing", t5, sizeof(t5) / sizeof(t5[0]), 6},
        {"all_zero", t6, sizeof(t6) / sizeof(t6[0]), 0},
        {"single", t7, sizeof(t7) / sizeof(t7[0]), 0},
        {"mixed", t8, sizeof(t8) / sizeof(t8[0]), 36},
    };

    int ntests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < ntests; ++i)
    {
        int got = maxArea(tests[i].arr, tests[i].size);
        if (got == tests[i].expected)
        {
            printf("PASS: %s -> %d\n", tests[i].name, got);
            passed++;
        }
        else
        {
            printf("FAIL: %s -> got %d, expected %d\n", tests[i].name, got,
                   tests[i].expected);
        }
    }

    printf("%d/%d tests passed\n", passed, ntests);
    return (passed == ntests) ? 0 : 1;
}
