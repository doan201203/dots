#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")

#include <bits/stdc++.h>

template <class T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <class T, class U = T> bool ckmin(T &a, U &&b) {
  return b < a ? a = std::forward<U>(b), true : false;
}

template <typename Distance, typename Graph>
auto dijkstra(int n, const Graph &g, int s) {
  std::vector d(n, std::numeric_limits<Distance>::max());
  std::vector prv(n, -1);
  struct P {
    Distance t;
    int v;
    bool operator>(const P &x) const { return t > x.t; }
    P(Distance _t, int _v) : t(_t), v(_v) {}
  };
  min_heap<P> heap;
  d[s] = 0;
  heap.emplace(d[s], s);
  while (!heap.empty()) {
    auto [dv, v] = heap.top();
    heap.pop();
    if (dv != d[v])
      continue;
    for (auto &&[to, w] : g[v])
      if (ckmin(d[to], dv + w))
        heap.emplace(d[to], to), prv[to] = v;
  }
  return std::make_pair(d, prv);
}

using namespace std;

int main() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  struct edge {
    int x, y;
  };
  graph_edge_pointers<int> g(n, m);
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    g.add_edge(u, v, w);
  }
  auto [d, prv] = dijkstra<int64_t>(n, g, s);
  if (d[t] == numeric_limits<int64_t>::max()) {
    cout << -1 << '\n';
  } else {
    vector<int> res{t};
    for (int cur = t; cur != s; cur = prv[cur])
      res.emplace_back(prv[cur]);
    cout << d[t] << ' ' << res.size() - 1 << '\n';
    for (int i = int(res.size()) - 1; i > 0; --i) {
      cout << res[i] << ' ' << res[i - 1] << '\n';
    }
  }
}
