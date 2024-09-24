#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> hash;

    int n;
    for (int i = 0; i < nums.size(); i++) {
      n = target - nums[i];
      if (hash.find(n) != hash.end()) {
        return {hash[n], i};
      }
      hash[nums[i]] = i;
    }

    return {0, 0};
  }
};

int main() {
  Solution s;
  vector<int> nums;
  vector<int> result;

  nums = {2, 7, 11, 15};
  result = s.twoSum(nums, 9);
  cout << result[0] << " " << result[1] << endl;

  nums = {3, 2, 4};
  result = s.twoSum(nums, 6);
  cout << result[0] << " " << result[1] << endl;

  nums = {3, 3};
  result = s.twoSum(nums, 6);
  cout << result[0] << " " << result[1] << endl;

  return 0;
}
