#include <iostream>
#include <map>
#include <cmath>
 
using namespace std;
 
#define MAX_N 150 
 
int nums[MAX_N][2000];
map<int, int> occ;
 
int main() {
  int t, n, q;
  cin >> t;
  while (t--) {
    int calculated = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      nums[0][i] = x;
    }
    cin >> q;
    int mn = 2 * sqrt(2*n);
    for (int i = 0; i < q; i++) {
      int a, k;
      cin >> a >> k;
      k = min(k, mn);
      while (k > calculated) {
        occ.clear();
        for (int j = 0; j < n; j++) {
          occ[nums[calculated][j]]++;
        }
        for (int j = 0; j < n; j++) {
          nums[calculated+1][j] = occ[nums[calculated][j]];
        }
        calculated++;
      }
      cout << nums[k][a-1] << endl;
    }
  }
 
  return 0;
}
