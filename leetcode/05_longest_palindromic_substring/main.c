#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Manacher's Algorithm - O(n) time complexity
 *
 * Key idea:
 * 1. Preprocess string by inserting '#' between characters
 *    This handles both even and odd length palindromes uniformly
 *    Example: "babad" -> "#b#a#b#a#d#"
 *
 * 2. Use an array P where P[i] = radius of palindrome centered at i
 *
 * 3. Keep track of the rightmost boundary (right) and the center of that
 * palindrome (center) Let left = 2*center - right. If i is within [left,
 * right], P[i] can be initialized using P[mirror_i], where mirror_i = 2*center
 * - i
 *
 * Time: O(n), Space: O(n)
 *
 * ============ STEP-BY-STEP EXAMPLE: "racecar" ============
 *
 * Step 1: PREPROCESSING
 * Original:   r a c e c a r
 * Index:      0 1 2 3 4 5 6
 *
 * Add '#' between each character:
 * Processed:  # r # a # c # e # c # a # r #
 * Index:      0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
 * Length = 2*7 + 1 = 15
 *
 * Step 2: BUILD P ARRAY (radius of palindrome at each center)
 * P[i] tells us: how many characters extend left & right from position i
 *
 * Process each position i from 1 to 14:
 *
 * i=1 (char 'r'): P[1]=0, center=0, right=0
 * i=2 (char '#'): P[2]=1 (can expand: #r#), center=2, right=3
 * i=3 (char 'a'): P[3]=0, mirror would help but we're expanding first time
 * i=4 (char '#'): P[4]=3 (#r#a#r#? No, only #a#), so P[4]=1
 * i=5 (char 'c'): P[5]=0
 * i=6 (char '#'): P[6]=5 (# c # a # c # = 5), expand: #cac#, center=6, right=11
 * i=7 (char 'e'): mirror=5, i < right, so use mirror property
 *                 P[7] = min(right-i, P[mirror]) = min(4, 0) = 0
 * i=8 (char '#'): mirror=4, P[4]=1, right-i=3
 *                 P[8] = min(3, 1) = 1, try expand: #e# ✓
 * i=9 (char 'c'): Use mirror: P[9]=P[5]=0, try expand: gets P[9]=5
 *                 (# c e c #) extends to entire palindrome!
 *                 center=9, right=14
 * i=10,11,12,13,14: Mirror property saves us!
 *
 * Step 3: FIND MAXIMUM
 * The longest radius found: max_len = 7 at center_index = 9
 *
 * Step 4: EXTRACT FROM ORIGINAL
 * start = (center_index - max_len) / 2
 *       = (9 - 7) / 2
 *       = 2 / 2
 *       = 1
 *
 * Result = s[1..7] = "racecar" ✓
 *
 * VISUALIZATION (CENTER + MIRROR PROPERTY):
 * Current rightmost palindrome window: [left .. right]
 * where left = 2*center - right
 *
 * left      mirror        center          i         right
 *  |          |             |             |           |
 *  *----------*-------------*-------------*-----------*
 *
 * If i is inside [left, right]:
 *   mirror_i = 2*center - i
 *   P[i] starts from min(right - i, P[mirror_i])
 * Then expand around i while both sides match.
 */
char *longestPalindrome(char *s)
{
    if (s == NULL || strlen(s) == 0)
    {
        char *result = (char *)malloc(1);
        result[0] = '\0';
        return result;
    }

    int n = strlen(s);

    // Create preprocessed string with '#' separators
    // Length will be 2*n + 3 (for leading/trailing '#' and null terminator)
    char *processed = (char *)malloc(2 * n + 3);
    processed[0] = '#';

    for (int i = 0; i < n; i++)
    {
        processed[2 * i + 1] = s[i];
        processed[2 * i + 2] = '#';
    }
    int processed_len = 2 * n + 1;
    processed[processed_len] = '\0';

    // P[i] = radius of palindrome centered at i
    int *P = (int *)malloc(processed_len * sizeof(int));
    memset(P, 0, processed_len * sizeof(int));

    int center = 0; // Center of the rightmost palindrome
    int right = 0;  // Right boundary of the rightmost palindrome
    int max_len = 0;
    int center_index = 0;

    for (int i = 1; i < processed_len; i++)
    {
        // Mirror of i with respect to center
        int mirror = 2 * center - i;

        // If i is within the right boundary, we can use previously computed
        // values
        if (i < right)
        {
            P[i] = (right - i < P[mirror]) ? (right - i) : P[mirror];
        }

        // Try to expand palindrome centered at i
        while (i + P[i] + 1 < processed_len && i - P[i] - 1 >= 0 &&
               processed[i + P[i] + 1] == processed[i - P[i] - 1])
        {
            P[i]++;
        }

        // If palindrome centered at i extends past right, update center and
        // right
        if (i + P[i] > right)
        {
            center = i;
            right = i + P[i];
        }

        // Track the longest palindrome
        if (P[i] > max_len)
        {
            max_len = P[i];
            center_index = i;
        }
    }

    // Extract the longest palindrome from original string
    // Starting position in original string = (center_index - max_len) / 2
    // Length = max_len
    int start = (center_index - max_len) / 2;
    char *result = (char *)malloc(max_len + 1);
    strncpy(result, s + start, max_len);
    result[max_len] = '\0';

    free(processed);
    free(P);

    return result;
}

// Visualize center, right boundary, and current index on processed string.
void printCenterVisualization(char *processed, int processed_len, int center,
                              int right, int current)
{
    int left = 2 * center - right;
    if (left < 0)
        left = 0;

    printf("    Processed: ");
    for (int i = 0; i < processed_len; i++)
        printf("%c ", processed[i]);
    printf("\n");

    printf("    Index:     ");
    for (int i = 0; i < processed_len; i++)
        printf("%2d ", i);
    printf("\n");

    printf("    Center:    ");
    for (int i = 0; i < processed_len; i++)
        printf(i == center ? "^ " : "  ");
    printf("\n");

    printf("    Current:   ");
    for (int i = 0; i < processed_len; i++)
        printf(i == current ? "^ " : "  ");
    printf("\n");

    printf("    Right:     ");
    for (int i = 0; i < processed_len; i++)
        printf(i == right ? "^ " : "  ");
    printf("\n");

    printf("    Active window: [%d..%d]\n", left, right);
}

// Debug version with detailed step-by-step visualization
void debugManacher(char *s)
{
    printf("====== DETAILED WALKTHROUGH: \"%s\" ======\n\n", s);

    if (s == NULL || strlen(s) == 0)
    {
        printf("Empty string - result: \"\"\n\n");
        return;
    }

    int n = strlen(s);

    // Step 1: Preprocessing
    printf("STEP 1: PREPROCESSING\n");
    printf("Original:  ");
    for (int i = 0; i < n; i++)
        printf("%c ", s[i]);
    printf("\nIndex:     ");
    for (int i = 0; i < n; i++)
        printf("%d ", i);

    char *processed = (char *)malloc(2 * n + 3);
    processed[0] = '#';
    for (int i = 0; i < n; i++)
    {
        processed[2 * i + 1] = s[i];
        processed[2 * i + 2] = '#';
    }
    int processed_len = 2 * n + 1;
    processed[processed_len] = '\0';

    printf("\n\nProcessed: ");
    for (int i = 0; i < processed_len; i++)
        printf("%c ", processed[i]);
    printf("\nIndex:     ");
    for (int i = 0; i < processed_len; i++)
        printf("%2d ", i);
    printf("\nLength = 2*%d + 1 = %d\n\n", n, processed_len);

    // Step 2: Build P array with visualization
    printf("STEP 2: BUILD P ARRAY (radius at each center)\n\n");

    int *P = (int *)malloc(processed_len * sizeof(int));
    memset(P, 0, processed_len * sizeof(int));

    int center = 0;
    int right = 0;
    int max_len = 0;
    int center_index = 0;

    printf("Legend: Center='^' on Center row, current i='^' on Current row, "
           "right boundary='^' on Right row\n\n");

    for (int i = 1; i < processed_len; i++)
    {
        printCenterVisualization(processed, processed_len, center, right, i);

        int mirror = 2 * center - i;

        printf("i=%2d (char '%c'): ", i, processed[i]);

        if (i < right)
        {
            P[i] = (right - i < P[mirror]) ? (right - i) : P[mirror];
            printf("mirror_i=%d, P[mirror]=%d, right-i=%d -> P[i]=%d initially",
                   mirror, P[mirror], right - i, P[i]);
        }

        int expanded = 0;
        while (i + P[i] + 1 < processed_len && i - P[i] - 1 >= 0 &&
               processed[i + P[i] + 1] == processed[i - P[i] - 1])
        {
            P[i]++;
            expanded = 1;
        }

        if (expanded || (i >= right))
            printf(" -> expanded to P[i]=%d", P[i]);

        if (i + P[i] > right)
        {
            center = i;
            right = i + P[i];
            printf(" | NEW: center=%d, right=%d", center, right);
        }

        if (P[i] > max_len)
        {
            max_len = P[i];
            center_index = i;
            printf(" | NEW MAX!");
        }
        printf("\n\n");
    }

    // Step 3: Show P array
    printf("\nP array: ");
    for (int i = 0; i < processed_len; i++)
        printf("%2d ", P[i]);
    printf("\n\n");

    // Step 4: Extract result
    printf("STEP 3: EXTRACT RESULT\n");
    printf("Max length found: %d at center index %d\n", max_len, center_index);
    printf("Start position = (center_index - max_len) / 2\n");
    printf("              = (%d - %d) / 2\n", center_index, max_len);
    printf("              = %d / 2\n", center_index - max_len);

    int start = (center_index - max_len) / 2;
    printf("              = %d\n\n", start);

    char *result = (char *)malloc(max_len + 1);
    strncpy(result, s + start, max_len);
    result[max_len] = '\0';

    printf("Result: \"%s\"\n\n", result);

    free(processed);
    free(P);
    free(result);
}

// Test function
void test(char *input, char *expected)
{
    char *result = longestPalindrome(input);

    printf("Input: \"%s\"\n", input);
    printf("Expected: \"%s\"\n", expected);
    printf("Got: \"%s\"\n", result);

    // For palindromes of same length, they're both valid
    int result_valid = 0;
    if (strlen(result) == strlen(expected))
    {
        // Check if result is a palindrome
        int is_palindrome = 1;
        int len = strlen(result);
        for (int i = 0; i < len / 2; i++)
        {
            if (result[i] != result[len - 1 - i])
            {
                is_palindrome = 0;
                break;
            }
        }

        // Check if result exists in input
        if (is_palindrome && strstr(input, result) != NULL)
        {
            result_valid = 1;
        }
    }

    printf("Status: %s\n\n", result_valid ? "✓ PASS" : "✗ FAIL");
    free(result);
}

int main(void)
{
    printf("=== STEP-BY-STEP VISUALIZATION ===\n\n");

    // Show detailed walkthrough for a few examples
    debugManacher("racecar");
    debugManacher("babad");
    debugManacher("cbbd");

    printf("\n\n=== ALL TEST CASES ===\n\n");

    // Test Case 1: Two palindromes of same length
    test("babad", "bab"); // or "aba"

    // Test Case 2: Even length palindrome
    test("cbbd", "bb");

    // Test Case 3: Single character
    test("a", "a");

    // Test Case 4: Single character (empty)
    test("ac", "a"); // or "c"

    // Test Case 5: Entire string is palindrome
    test("racecar", "racecar");

    // Test Case 6: Entire string is palindrome (even length)
    test("abba", "abba");

    // Test Case 7: No palindrome of length > 1
    test("abcdef", "a"); // or any single char

    // Test Case 8: Palindrome at beginning
    test("abaXYZ", "aba");

    // Test Case 9: Palindrome at end
    test("XYZaba", "aba");

    // Test Case 10: Long palindrome
    test("forgeeksskeegfor", "geeksskeeg");

    // Test Case 11: Nested palindromes
    test("abacabad", "abacaba");

    // Test Case 12: Empty string
    test("", "");

    // Test Case 13: Many repeating characters
    test("aaaa", "aaaa");

    // Test Case 14: Mixed case
    test("A man a plan a canal Panama", " a"); // spaces matter

    // Test Case 15: Special characters
    test("a@b@a", "a@b@a");

    return 0;
}