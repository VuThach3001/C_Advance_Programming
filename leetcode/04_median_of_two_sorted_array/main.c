/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).
Constraints:
    nums1.length == m
    nums2.length == n
    0 <= m <= 1000
    0 <= n <= 1000
    1 <= m + n <= 2000
    -106 <= nums1[i], nums2[i] <= 106
*/

#include <limits.h>

double findMedianSortedArrays (int* nums1, int m, int* nums2, int n)
{

    // Ensure nums1 is the smaller array
    if (m > n)
        return findMedianSortedArrays (nums2, n, nums1, m);

    int left = 0;
    int right = m;

    while (left <= right)
    {
        int partition1 = (left + right) / 2;
        int partition2 = (m + n + 1) / 2 - partition1;

        int maxLeft1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
        int minRight1 = (partition1 == m) ? INT_MAX : nums1[partition1];

        int maxLeft2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
        int minRight2 = (partition2 == n) ? INT_MAX : nums2[partition2];

        if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1)
        {
            // Correct partition
            if ((m + n) % 2 == 0)
            {
                int leftMax = maxLeft1 > maxLeft2 ? maxLeft1 : maxLeft2;
                int rightMin = minRight1 < minRight2 ? minRight1 : minRight2;
                return (leftMax + rightMin) / 2.0;
            }
            else
            {
                return (maxLeft1 > maxLeft2) ? maxLeft1 : maxLeft2;
            }
        }
        else if (maxLeft1 > minRight2)
        {
            right = partition1 - 1;
        }
        else
        {
            left = partition1 + 1;
        }
    }

    return 0.0;
}