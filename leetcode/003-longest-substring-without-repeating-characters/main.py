class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        used = set()
        curr = list()
        res = 0
        hi = 0

        for c in s:
            if c in used:
                while len(curr) > 0:
                    z = curr.pop(0)
                    used.remove(z)
                    res -= 1
                    if z == c:
                        break
            used.add(c)
            curr.append(c)
            res += 1
            hi = max(res, hi)

        return hi


s = Solution()
print(s.lengthOfLongestSubstring("abcabcbb"))
print(s.lengthOfLongestSubstring("bbbbb"))
print(s.lengthOfLongestSubstring("pwwkew"))
print(s.lengthOfLongestSubstring("aab"))
