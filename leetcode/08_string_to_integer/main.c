#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

int myAtoi(const char *s)
{
    int i = 0;
    // 1. Skip whitespace
    while (s[i] == ' ')
        i++;

    // 2. Handle sign
    //  2.1 Check if it is negative (-) -> sign = -1
    //  2.2 Skipp sign char
    int sign = 1;
    if (s[i] == '+' || s[i] == '-')
    {
        if (s[i] == '-')
            sign = -1;
        i++;
    }
    int result = 0;
    // 3. Process digits
    while (isdigit(s[i]))
    {
        int digit = s[i] - '0'; // Ex: s[i] = 'c' - '0' = 53 - 48 = 5;
        // 4. Overflow check -> Rounding
        if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > 7))
        {
            return sign == 1 ? INT_MAX : INT_MIN;
        }
        result = result * 10 + digit;
        i++;
    }
    return result * sign;
}

int main(void)
{
    struct
    {
        const char *s;
        int expected;
    } tests[] = {
        {"42", 42},
        {"   -42", -42},
        {"4193 with words", 4193},
        {"words and 987", 0},
        {"-91283472332", INT_MIN},
        {"2147483648", INT_MAX},
        {"+1", 1},
        {"+-2", 0},
        {"   +0 123", 0},
        {"00000-42a1234", 0},
        {"", 0},
        {"   ", 0},
        {"  -0012a42", -12},
        {"-2147483648", INT_MIN},
        {"2147483647", INT_MAX},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    int fails = 0;
    for (int i = 0; i < n; ++i)
    {
        int out = myAtoi(tests[i].s);
        printf("Input: \"%s\"\nOutput: %d  Expected: %d  %s\n\n", tests[i].s,
               out, tests[i].expected,
               out == tests[i].expected ? "PASS" : "FAIL");
        if (out != tests[i].expected)
            ++fails;
    }
    printf("Summary: %d tests, %d failures\n", n, fails);
    return fails ? 1 : 0;
}
