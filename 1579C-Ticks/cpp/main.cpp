#include <iostream>

using namespace std;

#define REP(n) for(int i = 0; i < n; i++)
#define FOR(i, n) for(int i = 0; i < n; i++)

int t, cols, rows, k;
int grid[19][10];

bool isInGrid(int x, int y) {
  return x >= 0 && x < cols && y >= 0 && y < rows;
}

int getMax(int x, int y) {
  int dist, nx1, nx2, ny;
  
  for (dist = 1; dist <= y; dist++) {
    nx1 = x - dist;
    nx2 = x + dist;
    ny = y - dist;

    if (!isInGrid(nx1, ny) || !isInGrid(nx2, ny)) return dist-1;
    if (isInGrid(nx1, ny) && grid[nx1][ny] < 0) return dist-1;
    if (isInGrid(nx2, ny) && grid[nx2][ny] < 0) return dist-1;
  }

  return dist;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> t;
  REP(t) {
    cin >> rows >> cols >> k;
    char ch = ' ';

    FOR(y, rows) {
      FOR(x, cols) {
        cin >> ch;
        if (ch == '*')
          grid[x][y] = 0;
        else
          grid[x][y] = -1;
      }
    }

    //solution
    for(int y = k; y < rows; y++) {
      for(int x = 0; x < cols; x++) {
        if (grid[x][y] >= 0) {
          int best = getMax(x, y);

          //cout << best << " at " << x << " " << y << endl;

          for (int dist = 0; dist <= best; dist++) {
            int nx1 = x - dist;
            int nx2 = x + dist;
            int ny = y - dist;

            if (isInGrid(nx1, ny) && grid[nx1][ny] < best) grid[nx1][ny] = best;
            if (isInGrid(nx2, ny) && grid[nx2][ny] < best) grid[nx2][ny] = best;
          }
        }
      }
    }

    //FOR(y, rows) {
    //  FOR(x, cols) {
    //    cout << grid[x][y] << "\t";
    //  }
    //  cout << endl;
    //}

    bool ok = true;
    FOR(x, cols) FOR(y, rows) if (grid[x][y] < k && grid[x][y] != -1) ok = false;
    cout << (ok ? "YES" : "NO") << endl;
  }

  return 0;
}
