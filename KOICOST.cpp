#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define int int64_t

class dsu {
  vector<int> e;

public:
  explicit dsu(int n) : e(n, -1) {}

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

  int size(const int x) {
    return -e[find(x)];
  }
};

struct edge {
  int x;
  int y;
  int w;

  bool operator<(const edge other) const {
    return w < other.w;
  }
};

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int mod = 1e9;
  int n, m;
  cin >> n >> m;
  vector<edge> edges(m);
  int weight = 0;
  for (edge &e : edges) {
    cin >> e.x >> e.y >> e.w;
    e.x--;
    e.y--;
    weight += e.w;
  }
  sort(edges.rbegin(), edges.rend());
  dsu comp(n);
  int ans = 0;
  for (const edge e : edges) {
    if (comp.find(e.x) != comp.find(e.y)) {
      ans += comp.size(e.x) * comp.size(e.y) * weight;
      ans %= mod;
      comp.unite(e.x, e.y);
    }
    weight -= e.w;
  }
  cout << ans << "\n";
}
