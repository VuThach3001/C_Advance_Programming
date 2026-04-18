#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Function declaration
double findMedianSortedArrays(int *nums1, int m, int *nums2, int n);

// Tolerance for double comparison
#define EPSILON 1e-9

// Test result structure
struct TestResult
{
    int testNumber;
    int passed;
    char description[256];
    double expected;
    double actual;
};

// Helper function to compare doubles with tolerance
int doubleEqual(double a, double b) { return fabs(a - b) < EPSILON; }

// Test runner function
struct TestResult runTest(int testNum, const char *desc, int *nums1, int m,
                          int *nums2, int n, double expected)
{
    struct TestResult result;
    result.testNumber = testNum;
    snprintf(result.description, sizeof(result.description), "%s", desc);
    result.expected = expected;
    result.actual = findMedianSortedArrays(nums1, m, nums2, n);
    result.passed = doubleEqual(result.actual, expected);

    return result;
}

// Print test result
void printTestResult(struct TestResult result)
{
    printf("Test %d: %s\n", result.testNumber, result.description);
    printf("        Expected: %.6f, Got: %.6f [%s]\n", result.expected,
           result.actual, result.passed ? "PASS" : "FAIL");
    printf("\n");
}

int main()
{
    printf("========================================\n");
    printf("  Median of Two Sorted Arrays - Test Suite\n");
    printf("========================================\n\n");

    struct TestResult results[30];
    int numTests = 0;

    // ====================
    // Test Case 1: Basic case with equal lengths
    // ====================
    {
        int arr1[] = {1, 3};
        int arr2[] = {2};
        results[numTests++] = runTest(
            1, "Example 1: [1,3] and [2], median = 2.0", arr1, 2, arr2, 1, 2.0);
    }

    // ====================
    // Test Case 2: Basic case with unequal lengths
    // ====================
    {
        int arr1[] = {0, 0};
        int arr2[] = {0, 0};
        results[numTests++] =
            runTest(2, "Example 2: [0,0] and [0,0], median = 0.0", arr1, 2,
                    arr2, 2, 0.0);
    }

    // ====================
    // Test Case 3: First array is empty
    // ====================
    {
        int arr1[] = {};
        int arr2[] = {1};
        results[numTests++] = runTest(
            3, "Edge case: Empty array []. Single element [1], median = 1.0",
            arr1, 0, arr2, 1, 1.0);
    }

    // ====================
    // Test Case 4: Second array is empty
    // ====================
    {
        int arr1[] = {2};
        int arr2[] = {};
        results[numTests++] = runTest(
            4, "Edge case: Single element [2], Empty array [], median = 2.0",
            arr1, 1, arr2, 0, 2.0);
    }

    // ====================
    // Test Case 5: Both arrays with multiple elements (odd total)
    // ====================
    {
        int arr1[] = {1, 2};
        int arr2[] = {3, 4, 5};
        results[numTests++] =
            runTest(5, "Case 5: [1,2] and [3,4,5], median = 3.0", arr1, 2, arr2,
                    3, 3.0);
    }

    // ====================
    // Test Case 6: Arrays with negative numbers
    // ====================
    {
        int arr1[] = {-5, -3, -1};
        int arr2[] = {-4, -2, 0};
        results[numTests++] =
            runTest(6, "Case 6: [-5,-3,-1] and [-4,-2,0], median = -2.5", arr1,
                    3, arr2, 3, -2.5);
    }

    // ====================
    // Test Case 7: Mixed positive and negative
    // ====================
    {
        int arr1[] = {-2, 0, 2};
        int arr2[] = {-1, 1, 3};
        results[numTests++] =
            runTest(7, "Case 7: [-2,0,2] and [-1,1,3], median = 0.5", arr1, 3,
                    arr2, 3, 0.5);
    }

    // ====================
    // Test Case 8: Large numbers near INT_MAX
    // ====================
    {
        int arr1[] = {1000000};
        int arr2[] = {1000000};
        results[numTests++] =
            runTest(8, "Case 8: [1000000] and [1000000], median = 1000000.0",
                    arr1, 1, arr2, 1, 1000000.0);
    }

    // ====================
    // Test Case 9: Median from first array primarily
    // ====================
    {
        int arr1[] = {1, 3, 5, 7, 9};
        int arr2[] = {2, 12, 15, 17, 20, 100};
        results[numTests++] = runTest(9,
                                      "Case 9: [1, 3, 5, 7, 9}] and [2, 12, "
                                      "15, 17, 20, 100], median = 9",
                                      arr1, 5, arr2, 6, 9);
    }

    // ====================
    // Test Case 10: Median from second array primarily
    // ====================
    {
        int arr1[] = {1, 2};
        int arr2[] = {3, 4, 5, 6};
        results[numTests++] =
            runTest(10, "Case 10: [1,2] and [3,4,5,6], median = 3.5", arr1, 2,
                    arr2, 4, 3.5);
    }

    // ====================
    // Test Case 11: All elements same
    // ====================
    {
        int arr1[] = {5, 5, 5};
        int arr2[] = {5, 5};
        results[numTests++] =
            runTest(11, "Case 11: [5,5,5] and [5,5], median = 5.0", arr1, 3,
                    arr2, 2, 5.0);
    }

    // ====================
    // Test Case 12: Completely separated arrays (ascending)
    // ====================
    {
        int arr1[] = {1, 2, 3};
        int arr2[] = {4, 5, 6};
        results[numTests++] =
            runTest(12, "Case 12: [1,2,3] and [4,5,6], median = 3.5", arr1, 3,
                    arr2, 3, 3.5);
    }

    // ====================
    // Test Case 13: Overlapping arrays
    // ====================
    {
        int arr1[] = {1, 3, 5};
        int arr2[] = {2, 4, 6};
        results[numTests++] =
            runTest(13, "Case 13: [1,3,5] and [2,4,6], median = 3.5", arr1, 3,
                    arr2, 3, 3.5);
    }

    // ====================
    // Test Case 14: Even total length
    // ====================
    {
        int arr1[] = {1, 2, 3, 4, 5};
        int arr2[] = {2, 3, 6};
        results[numTests++] =
            runTest(14, "Case 14: [1,2,3,4,5] and [2,3,6], median = 3.0", arr1,
                    5, arr2, 3, 3.0);
    }

    // ====================
    // Test Case 15: Single element each
    // ====================
    {
        int arr1[] = {1};
        int arr2[] = {3};
        results[numTests++] = runTest(15, "Case 15: [1] and [3], median = 2.0",
                                      arr1, 1, arr2, 1, 2.0);
    }

    // ====================
    // Test Case 16: Negative numbers crossing zero
    // ====================
    {
        int arr1[] = {-100, -50, 0};
        int arr2[] = {-75, -25, 25, 50};
        results[numTests++] = runTest(
            16, "Case 16: [-100,-50,0] and [-75,-25,25,50], median = -25.0",
            arr1, 3, arr2, 4, -25.0);
    }

    // ====================
    // Test Case 17: Large array and small array
    // ====================
    {
        int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int arr2[] = {10};
        results[numTests++] =
            runTest(17, "Case 17: [1..9] and [10], median = 5.5", arr1, 9, arr2,
                    1, 5.5);
    }

    // ====================
    // Test Case 18: Two arrays with 1 element each (small numbers)
    // ====================
    {
        int arr1[] = {0};
        int arr2[] = {0};
        results[numTests++] = runTest(18, "Case 18: [0] and [0], median = 0.0",
                                      arr1, 1, arr2, 1, 0.0);
    }

    // ====================
    // Test Case 19: Duplicate elements across arrays
    // ====================
    {
        int arr1[] = {1, 1, 1};
        int arr2[] = {1, 1, 1};
        results[numTests++] =
            runTest(19, "Case 19: [1,1,1] and [1,1,1], median = 1.0", arr1, 3,
                    arr2, 3, 1.0);
    }

    // ====================
    // Test Case 20: Descending when merged
    // ====================
    {
        int arr1[] = {2, 4};
        int arr2[] = {1, 3};
        results[numTests++] =
            runTest(20, "Case 20: [2,4] and [1,3], median = 2.5", arr1, 2, arr2,
                    2, 2.5);
    }

    // ====================
    // Print Summary
    // ====================
    printf("\n========================================\n");
    printf("  Test Results Summary\n");
    printf("========================================\n\n");

    int passed = 0;
    int failed = 0;

    for (int i = 0; i < numTests; i++)
    {
        printTestResult(results[i]);
        if (results[i].passed)
        {
            passed++;
        }
        else
        {
            failed++;
        }
    }
    printf("========================================\n");
    printf("Total Tests: %d\n", numTests);
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);
    printf("Success Rate: %.1f%%\n", (passed * 100.0) / numTests);
    printf("========================================\n");

    return failed == 0 ? 0 : 1;
}
