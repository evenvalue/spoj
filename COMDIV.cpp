#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  vector<int> divisor(1e6 + 5);
  iota(divisor.begin(), divisor.end(), 0);
  for (int i = 2; i < divisor.size(); i++) {
    if (divisor[i] != i) continue;
    for (int j = i + i; j <= 1e6 + 3; j += i) {
      divisor[j] = min(divisor[j], i);
    }
  }

  auto gcd = [](int x, int y) {
    while (y) {
      x %= y;
      swap(x, y);
    }
    return x;
  };

  int t;
  cin >> t;
  while (t--) {
    int a, b;
    cin >> a >> b;
    int prime = 2, pcnt = 0;
    int ans = 1;
    for (int factor = gcd(a, b); factor != 1; factor /= divisor[factor]) {
      const int cur = divisor[factor];
      if (cur == prime) {
        pcnt++;
      } else {
        ans *= pcnt + 1;
        prime = cur;
        pcnt = 1;
      }
    }
    cout << ans * (pcnt + 1) << "\n";
  }
}