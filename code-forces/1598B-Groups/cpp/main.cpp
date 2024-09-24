#include <iostream>

#define US unsigned short int

using namespace std;

int main() {
  US n_tests;
  US group[5][1000];
  US n_group[5];
  US checked[1000];
  bool done;

  US n_student;

  cin >> n_tests;
  for (int i_test = 0; i_test < n_tests; i_test++) {
    for(int i = 0; i < 5; i++) n_group[i] = 0;
    done = false;
    
    cin >> n_student;
    for(int i_student = 0; i_student < n_student; i_student++) {
      for (int i = 0; i < 5; i++) {
        int ok;
        cin >> ok;
        if (ok == 1) {
          group[i][n_group[i]] = i_student;
          n_group[i]++;
        }
      }
    }

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (n_group[i] < n_student/2 || n_group[j] < n_student/2) continue;
        if (i == j) continue;

        for (int k = 0; k < n_student; k++) checked[k] = 0;
        for (int k = 0; k < n_group[i]; k++) checked[group[i][k]]++;
        for (int k = 0; k < n_group[j]; k++) checked[group[j][k]]++;
        done = true;
        for (int k = 0; k < n_student; k++) {
          if (checked[k] == 0) done = false;
        }
      
        if(done) break;      
      }

      if(done) break;
    }

    if(done) cout << "YES"; else cout << "NO";

    cout << endl;
  }

  return 0;
} 
