
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
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
  }
  for (auto &v : g) {
    sort(v.rbegin(), v.rend());
  }
  vector<bool> visit(n, false);
  vector<bool> enter(n, false);
  vector<int> topsort;
  auto reject = []() {
    cout << "Sandro fails.\n";
    exit(0);
  };
  function<void(int)> dfs_cycle = [&](const int x) {
    visit[x] = enter[x] = true;
    for (const int y : g[x]) {
      if (enter[y]) reject();
      if (visit[y]) continue;
      dfs_cycle(y);
    }
    topsort.push_back(x);
    enter[x] = false;
  };
  for (int i = n - 1; i >= 0; i--) {
    if (not visit[i]) {
      dfs_cycle(i);
    }
  }
  reverse(topsort.begin(), topsort.end());
  for (const int x : topsort) {
    cout << x + 1 << " ";
  }
  cout << "\n";
}