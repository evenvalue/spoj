#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool check(const vector<int> &a, const int c, const int dist) {
  int prev = -1e6, cows = 0;
  for (int i = 0; i < a.size() and cows < c; i++) {
    if (prev + dist <= a[i]) {
      prev = a[i];
      cows++;
    }
  }
  return cows == c;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    for (int &pos : a) {
      cin >> pos;
    }
    sort(a.begin(), a.end());
    int lo = 0, hi = 1e9 + 10;
    while (lo < hi) {
      const int mid = (lo + hi + 1) / 2;
      if (check(a, c, mid)) {
        lo = mid;
      } else {
        hi = mid - 1;
      }
    }
    cout << lo << "\n";
  }
}