/* Zigzag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of
rows like this: (you may want to display this pattern in a fixed font for better
legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number
of rows:

string convert(string s, int numRows);


Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I
Example 3:

Input: s = "A", numRows = 1
Output: "A"


Constraints:

1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *my_strdup(const char *s)
{
    if (!s)
        return NULL;
    size_t n = strlen(s) + 1;
    char *p = malloc(n);
    if (p)
        memcpy(p, s, n);
    return p;
}

char *convert(char *s, int numRows)
{
    if (numRows == 1)
        return s;

    int len = strlen(s);
    char *result = (char *)malloc(len + 1);
    int pos = 0;

    // The cycle length is the number of characters in one full zigzag pattern
    int cycle = 2 * numRows - 2;

    for (int row = 0; row < numRows; row++)
    {
        for (int j = row; j < len; j += cycle)
        {
            result[pos++] = s[j];

            int diag = j + cycle - 2 * row;
            if (row != 0 && row != numRows - 1 && diag < len)
            {
                result[pos++] = s[diag];
            }
        }
    }
    result[pos] = '\0';
    return result;
}

static void run_test(const char *s, int numRows, const char *expect)
{
    char *input = my_strdup(s);
    char *out = convert(input, numRows);
    printf("s=\"%s\", numRows=%d -> %s\n", s, numRows, out ? out : "(null)");
    if (expect)
    {
        if (out && strcmp(out, expect) == 0)
            printf("  [OK] matches expected: %s\n", expect);
        else
            printf("  [FAIL] expected: %s\n", expect);
    }
    if (out == input)
        free(out);
    else
    {
        free(input);
        free(out);
    }
}

int main(void)
{
    // Provided LeetCode examples and some edge cases
    run_test("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR");
    run_test("PAYPALISHIRING", 4, "PINALSIGYAHRPI");
    run_test("A", 1, "A");
    run_test("", 1, "");
    run_test("HELLO", 2, "HLOEL");

    return 0;
}
