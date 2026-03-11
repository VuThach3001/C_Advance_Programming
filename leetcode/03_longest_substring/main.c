/*
Given a string s, find the length of the longest substring without duplicate characters.

Strategy: Sliding Window + Hash Map
- Maintain a window [left, right] that always contains unique characters.
- Use an array (charIndex[128]) to store the last seen index+1 of each ASCII character.
- For each new character s[right], if it was seen inside the current window,
  shrink the window by moving left past the previous occurrence.
- Track the maximum window size seen at each step.

Time:  O(n)  — each character is visited at most twice (once by right, once by left)
Space: O(1)  — fixed-size array of 128 ASCII entries
*/

#include <string.h>
#include <stdio.h>

int lengthOfLongestSubstring (char* s);

int main (void)
{
    /* Test case 1: expected 3 ("abc") */
    printf ("lengthOfLongestSubstring(\"aba\") = %d\n",
            lengthOfLongestSubstring ("aba"));

    /* Test case 2: expected 1 ("b") */
    printf ("lengthOfLongestSubstring(\"bbbbb\")    = %d\n",
            lengthOfLongestSubstring ("bbbbb"));

    /* Test case 3: expected 3 ("wke") */
    printf ("lengthOfLongestSubstring(\"pwwkew\")   = %d\n",
            lengthOfLongestSubstring ("pwwkew"));

    /* Test case 4: expected 0 (empty string) */
    printf ("lengthOfLongestSubstring(\"\")         = %d\n",
            lengthOfLongestSubstring (""));

    return 0;
}

int lengthOfLongestSubstring (char* s)
{
    /* Stores the next valid left boundary for each ASCII character (0 = never seen) */
    int charIndex[128] = { 0 };

    int maxLen = 0; /* Length of the longest unique-character window found so far */
    int left = 0; /* Left boundary of the current sliding window */

    /* Expand the window one character at a time with 'right' */
    for (int right = 0; s[right] != '\0'; right++)
    {
        /* If the character was seen inside the current window, move left to be the same index as right to reset */
        if (charIndex[(int)s[right]] > left)
        {
            left = charIndex[(int)s[right]];
        }

        /* Record that s[right] was last seen at index 'right'; next valid left = right+1 */
        charIndex[(int)s[right]] = right + 1;

        /* Update the maximum window length */
        int currentLen = right - left + 1;
        if (currentLen > maxLen)
        {
            maxLen = currentLen;
        }
    }

    return maxLen;
}
