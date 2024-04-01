#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

#define sz(x) (int)x.size()
using i64 = long long;

const int N = 1e5 + 10;
int a[N], in[N], out[N], t, n, q, dep[N];
vector<int> g[N];

void dfs(int u, int p) {
  in[u] = ++t;
  for (int v : g[u]) {
    if (v == p)
      continue;
    dfs(v, u);
  }
  out[u] = ++t;
}

void solve() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i + 1 < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  dfs(1, 0);

  // 1 2 5 5 4 4 2 3 6 6 3 1
  //
}

int32_t main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int TC = 1;
  // cin >> TC;
  while (TC--) {
    solve();
  }
}
