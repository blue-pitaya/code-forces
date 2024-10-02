class Solution {
    public boolean isPalindrom(String base, int start, int end) {
        for (int i = 0; start + i < end - i; i++) {
            if (base.charAt(start + i) != base.charAt(end - i)) {
                return false;
            }
        }

        return true;
    }

    public String longestPalindrome(String s) {
        int bestStart = 0, bestEnd = 0;

        for (int i = 0; i < s.length(); i++) {
            for (int j = i; j < s.length(); j++) {
                if (isPalindrom(s, i, j)) {
                    if (j - i > bestEnd - bestStart) {
                        bestStart = i;
                        bestEnd = j;
                    }
                }
            }
        }

        return s.substring(bestStart, bestEnd + 1);
    }
}
