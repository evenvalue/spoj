#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  while (cin >> n >> m) {
    if (n == 0 and m == 0) break;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
      int x, y;
      cin >> x >> y;
      x--, y--;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    vector<bool> visit(n, false), artp(n, false);
    vector<int> tin(n, -1), low(n, -1);
    int timer = 0;
    function<void(int, int)> dfs = [&](const int x, const int p) {
      visit[x] = true;
      tin[x] = low[x] = timer++;
      int children = 0;
      for (const int y : g[x]) {
        if (y == p) continue;
        if (visit[y]) {
          low[x] = min(low[x], tin[y]);
        } else {
          dfs(y, x);
          low[x] = min(low[x], low[y]);
          artp[x] = artp[x] or (p != -1 and low[y] >= tin[x]);
          children++;
        }
      }
      if (p == -1) artp[x] = (children > 1);
    };
    dfs(0, -1);
    cout << count(artp.begin(), artp.end(), true) << '\n';
  }
}