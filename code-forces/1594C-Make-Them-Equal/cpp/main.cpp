#include <iostream>

using namespace std;

int n_test, str_size;
char ch;

int main() {
  cin >> n_test;

  for(int i_test = 0; i_test < n_test; i_test++) {
    cin >> str_size >> ch;

    bool ok = true;
    int last = -1;
    char curr;

    for(int i = 0; i < str_size; i++) {
      cin >> curr;
      if (curr == ch) last = i; else ok = false;
    }
    
    if (ok) cout << "0";
    else if (last >= str_size / 2) cout << "1" << endl << last + 1; 
    else cout << "2" << endl << str_size - 1 << " " << str_size;

    cout << endl;
  }

  return 0;
}
