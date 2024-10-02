import java.util.LinkedList;

class Solution {
    public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
        LinkedList<Integer> all = new LinkedList<>();
        int i1 = 0;
        int i2 = 0;

        while (i1 < nums1.length && i2 < nums2.length) {
            if (nums1[i1] < nums2[i2]) {
                all.add(nums1[i1]);
                i1++;
            } else {
                all.add(nums2[i2]);
                i2++;
            }
        }

        for (int i = i1; i < nums1.length; i++) {
            all.add(nums1[i]);
        }

        for (int i = i2; i < nums2.length; i++) {
            all.add(nums2[i]);
        }

        if (all.size() == 1) {
            return (double) all.get(0);
        } else if (all.size() % 2 == 0) {
            int mid1 = all.get(all.size() / 2 - 1);
            int mid2 = all.get(all.size() / 2);

            return ((double) mid1 + (double) mid2) / 2.0;
        } else {
            return (double) all.get(all.size() / 2);
        }
    }

    // faster solution
    public static double findMedianSortedArrays2(int[] nums1, int[] nums2) {
        int i1 = 0;
        int i2 = 0;
        int n = nums1.length + nums2.length;
        int lookup1 = 0, lookup2 = 0;

        for (int i = 0; i <= n / 2; i++) {
            if (i1 < nums1.length && i2 < nums2.length) {
                if (i == n / 2 - 1) {
                    lookup1 = Math.min(nums1[i1], nums2[i2]);
                }
                if (i == n / 2) {
                    lookup2 = Math.min(nums1[i1], nums2[i2]);
                }

                if (nums1[i1] < nums2[i2]) {
                    i1++;
                } else {
                    i2++;
                }
            } else if (i1 == nums1.length) {
                if (i == n / 2 - 1) {
                    lookup1 = nums2[i2];
                }
                if (i == n / 2) {
                    lookup2 = nums2[i2];
                }

                i2++;
            } else {
                if (i == n / 2 - 1) {
                    lookup1 = nums1[i1];
                }
                if (i == n / 2) {
                    lookup2 = nums1[i1];
                }

                i1++;
            }
        }

        if (n % 2 == 0) {
            return ((double) lookup1 + (double) lookup2) / 2.0;
        } else {
            return (double) lookup2;
        }
    }

    // binary search solution
    public static double findMedianSortedArrays3(int[] nums1, int[] nums2) {
        if (nums1.length > nums2.length) {
            findMedianSortedArrays3(nums2, nums1);
        }

        //TODO: better solution

        return 0;
    }

    public static void main(String[] args) {
        int[] nums1 = new int[] { 1, 8, 9 };
        int[] nums2 = new int[] { 2, 3, 4, 15, 16 };

        // int[] nums1 = new int[] { 1, 2 };
        // int[] nums2 = new int[] { 3, 4 };

        System.out.println(findMedianSortedArrays2(nums1, nums2));
    }
}
