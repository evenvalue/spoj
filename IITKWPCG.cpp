#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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

int log(long long x) {
  int res = 0;
  while (x != 1) {
    x >>= 1;
    res++;
  }
  return res;
}

int main() {
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
      long long x;
      cin >> e.x >> e.y >> x;
      e.x--;
      e.y--;
      e.w = log(x);
    }
    dsu kruskal(n);
    sort(edges.begin(), edges.end());
    int ans = 1;
    for (edge &e : edges) {
      if (kruskal.unite(e.x, e.y)) {
        ans += e.w;
      }
    }
    cout << ans << "\n";
  }
}