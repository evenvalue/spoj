#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#define int int64_t

class dsu {
  vector<int> e;

public:
  explicit dsu(const int n) : e(n, -1) {}

  int find(const int x) {
    return e[x] < 0 ? x : (e[x] = find(e[x]));
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y];
    e[y] = x;
    return true;
  }
};

struct edge {
  int x;
  int y;
  int w;

  bool operator<(const edge &other) const {
    return w < other.w;
  }
};

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<edge> edges(m);
    for (edge &e : edges) {
      cin >> e.x >> e.y >> e.w;
      e.x--;
      e.y--;
    }
    sort(edges.rbegin(), edges.rend());
    dsu kruskal(n);
    vector<vector<pair<int, int>>> mst(n); //maximum spanning tree.
    for (const edge &e : edges) {
      if (kruskal.unite(e.x, e.y)) {
        mst[e.x].push_back({e.y, e.w});
        mst[e.y].push_back({e.x, e.w});
      }
    }
    if (kruskal.unite(0, n - 1)) {
      cout << -1 << "\n";
      continue;
    }
    vector<int> speed(n);
    function<void(const int, const int)> dfs = [&](const int x, const int p) {
      for (const auto &nbr : mst[x]) {
        if (nbr.first == p) continue;
        speed[nbr.first] = min(speed[x], nbr.second);
        dfs(nbr.first, x);
      }
    };
    for (const auto &nbr : mst[0]) {
      speed[nbr.first] = nbr.second;
      dfs(nbr.first, 0);
    }
    cout << speed[n - 1] << "\n";
  }
}