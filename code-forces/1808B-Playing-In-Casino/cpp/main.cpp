#include <iostream>

using namespace std;

// TODO: better solution with quicksort quicksorting each column

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t,n,m,sum,x;

  cin >> t;

  for (int ti = 0; ti < t; ti++) {
    sum = 0;
    cin >> n >> m;

    int **nums = new int*[n];
    for (int i = 0; i < n; i++) {
      nums[i] = new int[m];
    }

    for (int ni = 0; ni < n; ni++) {
      for (int mi = 0; mi < m; mi++) {
        cin >> nums[ni][mi];
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
        for (int k = 0; k < m; k++) {
          x = nums[i][k] - nums[j][k];
          sum += (x < 0 ? x * -1 : x);
        }
      }
    }

    for(int i = 0; i < n; i++) {
      delete [] nums[i];
    }
    delete [] nums;

    cout << sum << endl;
  }

  return 0;
}
