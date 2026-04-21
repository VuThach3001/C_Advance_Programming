/*
9. Palindrome Number
Given an integer x, return true if x is a palindrome, and false otherwise.

Example 1:

Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

Example 2:

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes
121-. Therefore it is not a palindrome.

Example 3:

Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

Constraints:

    -231 <= x <= 231 - 1
*/
#include <stdio.h>

#include <stdbool.h>

/*
 Optimal approach: reverse half of the number and compare.

 Idea:
 - Negative numbers are not palindromes.
 - Numbers that end with 0 are not palindromes unless the number is 0.
 - Reverse the lower half of digits and stop when the reversed half >= remaining
 half.
 - For odd-length numbers, drop the middle digit by `rev/10` (middle is checked
 in the converting process) before comparing.

 Complexity: O(log10(n)) time, O(1) space.
*/

bool isPalindrome(int x)
{
    int org = x;
    int rev = 0;

    while (x > 0)
    {
        rev = rev * 10 + x % 10;
        x /= 10;
    }
    return org == rev;
}

int main(void)
{
    int tests[] = {121, -121, 10, 0, 12321, 1221, 1001, 2147447412};
    int n = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n; ++i)
    {
        int val = tests[i];
        printf("x = %d -> %s\n", val, isPalindrome(val) ? "true" : "false");
    }

    return 0;
}