#include <iostream>

using namespace std;

#define REP(n) for(int i = 0; i < n; i++)
#define FOR(i, n) for(int i = 0; i < n; i++)

int t, n;

bool isOk() {
  int k = n;
  while (k >= 0) {
    if (k % 11 == 0) return true;
    k -= 111;
  }
  
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> t;
  REP(t) {
    cin >> n;
    cout << (isOk() ? "YES" : "NO") << endl;
  }

  return 0;
}
