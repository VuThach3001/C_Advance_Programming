/* REVERSE INTEGER
   Optimal O(d) solution using overflow checks (32-bit signed int)
   Returns 0 when reverse would overflow 32-bit signed range.
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int reverse(int x)
{
    int rev = 0;
    while (x != 0)
    {
        int pop = x % 10;
        x /= 10;
        if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7))
            return 0;
        if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8))
            return 0;
        rev = rev * 10 + pop;
    }
    return rev;
}

static void run_test(int x, int expect)
{
    int out = reverse(x);
    if (out == expect)
        printf("x=%d -> %d  [OK]\n", x, out);
    else
        printf("x=%d -> %d  [FAIL] expected %d\n", x, out, expect);
}

int main(void)
{
    // Basic cases
    run_test(123, 321);
    run_test(-123, -321);
    run_test(120, 21);
    run_test(0, 0);

    // Overflow cases (should return 0)
    run_test(1534236469, 0); // reversed would overflow
    run_test(1000000003, 0); // reversed would overflow
    run_test(INT_MAX, 0);
    run_test(INT_MIN, 0);

    return 0;
}
