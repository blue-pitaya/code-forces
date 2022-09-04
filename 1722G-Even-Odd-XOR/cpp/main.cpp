#include <iostream>

using namespace std;

#define REP(n) for(int i = 0; i < n; i++)
#define FOR(i, n) for(int i = 0; i < n; i++)

#define MAX_INT 2147483647
#define MIN_INT -2147483648

int t, n;

int bitNumber(int n) {
  if (n <= 0) return 1;
  int bits = 0;
  while (n != 0) {
    bits++;
    n /= 2;
  }
  return bits;
}

int pow(int a, int n) {
  int res = 1;
  REP(n) {
    res *= a;
  }
  return res;
}

void foo(int n) {
  //start with 0,1,2...
  int res = 0;
  int bitnum, l1, l2; //last 1, last 2

  int startNum = -1;
  do {
    startNum++;
    res = 0;
    for (int i = startNum; i < n-2+startNum; i++) res = i ^ res;
  } while (res == 0);

  if (res != 0) {
    bitnum = bitNumber(res);
    l1 = (MAX_INT << bitnum) ^ MIN_INT;
    l2 = l1 + res;
  }

  for (int i = startNum; i < n-2+startNum; i++) cout << i << " ";
  cout << l1 << " " << l2 << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> t;
  REP(t) {
    cin >> n;
    foo(n);
  }

  return 0;
}
