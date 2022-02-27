#include <iostream>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  unsigned short w;
  cin >> w;
  
  if (w > 2 && ((w & 1) == 0)) cout << "YES" << endl;  
  else cout << "NO" << endl; 

  return 0;
}
