#include <iostream>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int tests, n, x, sum;
  cin >> tests;

  for (int t = 0; t < tests; t++) {
    sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> x;
      sum += max(x, 1);
    }
    cout << sum << endl;
  }
}
