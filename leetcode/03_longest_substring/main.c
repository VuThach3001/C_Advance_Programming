/*
Given a string s, find the length of the longest substring without duplicate
characters.

Strategy: Sliding Window + Hash Map
- Maintain a window [left, right] that always contains unique characters.
- Use an array (charIndex[128]) to store the last seen index+1 of each ASCII
character.
- For each new character s[right], if it was seen inside the current window,
  shrink the window by moving left past the previous occurrence.
- Track the maximum window size seen at each step.

Time:  O(n)  — each character is visited at most twice (once by right, once by
left) Space: O(1)  — fixed-size array of 128 ASCII entries
*/

#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char *s);

int main(void)
{
    /* Test case 1: expected 3 ("abc") */
    printf("lengthOfLongestSubstring(\"abcadaaa\") = %d\n",
           lengthOfLongestSubstring("abcadaaa"));

    /* Test case 2: expected 1 ("b") */
    printf("lengthOfLongestSubstring(\"bbbbb\")    = %d\n",
           lengthOfLongestSubstring("bbbbb"));

    /* Test case 3: expected 3 ("wke") */
    printf("lengthOfLongestSubstring(\"pwwkew\")   = %d\n",
           lengthOfLongestSubstring("pwwkew"));

    /* Test case 4: expected 0 (empty string) */
    printf("lengthOfLongestSubstring(\"\")         = %d\n",
           lengthOfLongestSubstring(""));

    return 0;
}

int lengthOfLongestSubstring(char *s)
{
    /* Create a sliding window */
    int charIndex[128] = {0};
    int left = 0;
    int maxLength = 0;
    int right = 0;
    while (s[right] != '\0')
    {

        if (charIndex[(int)s[right]] > left)
        {
            left = charIndex[(int)s[right]];
        }
        charIndex[(int)s[right]] = right + 1;

        int currentLen = right - left + 1;
        if (currentLen > maxLength)
        {
            maxLength = currentLen;
        }
        right++;
    }
    return maxLength;
}
