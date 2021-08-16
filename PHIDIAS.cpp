#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int w, h;
    cin >> w >> h;
    vector<vector<int>> waste(w + 1, vector<int>(h + 1, w * h));
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
      int l, b;
      cin >> l >> b;
      waste[l][b] = 0;
    }
    for (int i = 1; i <= w; i++) {
      for (int j = 1; j <= h; j++) {
        waste[i][j] = min(waste[i][j], i * j);
        for (int vcut = 1; vcut < j; vcut++) {
          waste[i][j] = min(waste[i][j], waste[i][vcut] + waste[i][j - vcut]);
        }
        for (int hcut = 1; hcut < i; hcut++) {
          waste[i][j] = min(waste[i][j], waste[hcut][j] + waste[i - hcut][j]);
        }
      }
    }
    cout << waste[w][h] << "\n";
  }
}