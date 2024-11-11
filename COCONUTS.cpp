#include <bits/stdc++.h>
using namespace std;

template<typename T>
T read() {
  T x;
  cin >> x;
  return x;
}

struct FlowEdge {
  int v, u;
  long long cap, flow = 0;
  FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
  const long long flow_inf = 1e18;
  vector<FlowEdge> edges;
  vector<vector<int>> adj;
  int n, m = 0;
  int s, t;
  vector<int> level, ptr;
  queue<int> q;

  Dinic(int n, int s, int t) : n(n), s(s), t(t) {
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }

  void add_edge(int v, int u, long long fwd, long long bwd) {
    edges.emplace_back(v, u, fwd);
    edges.emplace_back(u, v, bwd);
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
  }

  bool bfs() {
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : adj[v]) {
        if (edges[id].cap == edges[id].flow)
          continue;
        if (level[edges[id].u] != -1)
          continue;
        level[edges[id].u] = level[v] + 1;
        q.push(edges[id].u);
      }
    }
    return level[t] != -1;
  }

  long long dfs(int v, long long pushed) {
    if (pushed == 0)
      return 0;
    if (v == t)
      return pushed;
    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
      int id = adj[v][cid];
      int u = edges[id].u;
      if (level[v] + 1 != level[u])
        continue;
      long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0)
        continue;
      edges[id].flow += tr;
      edges[id ^ 1].flow -= tr;
      return tr;
    }
    return 0;
  }

  long long flow() {
    long long f = 0;
    while (true) {
      fill(level.begin(), level.end(), -1);
      level[s] = 0;
      q.push(s);
      if (!bfs())
        break;
      fill(ptr.begin(), ptr.end(), 0);
      while (long long pushed = dfs(s, flow_inf)) {
        f += pushed;
      }
    }
    return f;
  }
};

inline bool solution() {
  const int n = read<int>();
  const int m = read<int>();

  if (n == 0 and m == 0) return false;

  auto source = [&]() { return n; };
  auto sink = [&]() { return n + 1; };

  Dinic g(n + 2, source(), sink());

  for (int i = 0; i < n; i++) {
    const int x = read<int>();
    g.add_edge((x ? source() : sink()), i, 1, 1);
  }

  for (int i = 0; i < m; i++) {
    const int x = read<int>() - 1;
    const int y = read<int>() - 1;
    g.add_edge(x, y, 1, 1);
  }

  cout << g.flow() << '\n';

  return true;
}


int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  while (solution()) {}
}