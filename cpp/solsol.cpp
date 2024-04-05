// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define pb push_back

const int N = 300001;
vi g[N];
int in[N], sz[N], dep[N], pa[N][19], hld[N], cnt;
ll st[N << 2], lz[N << 2];
void dfs_size(int u, int p) {
  sz[u] = 1;
  pa[u][0] = p;
  for (int i = 1; i <= 18; i++)
    pa[u][i] = pa[pa[u][i - 1]][i - 1];
  for (int &v : g[u]) {
    g[v].erase(find(g[v].begin(), g[v].end(), u));
    if (v != p) {
      dep[v] = dep[u] + 1;
      dfs_size(v, u);
      sz[u] += sz[v];
      if (sz[g[u][0]] < sz[v])
        swap(g[u][0], v);
    }
  }
}
void dfs_hld(int u, int p) {
  in[u] = ++cnt;
  for (int &v : g[u])
    if (v != p) {
      hld[v] = (v == g[u][0] ? hld[u] : v);
      dfs_hld(v, u);
    }
}
int n, q;
void push(int v) {
  st[v << 1] += lz[v];
  lz[v << 1] += lz[v];
  st[v << 1 | 1] += lz[v];
  lz[v << 1 | 1] += lz[v];
  lz[v] = 0;
}

void upd(int v, int tl, int tr, int l, int r, ll addend) {
  if (l > r)
    return;
  if (l == tl && tr == r) {
    st[v] += addend;
    lz[v] += addend;
  } else {
    push(v);
    int tm = (tl + tr) >> 1;
    upd(v << 1, tl, tm, l, min(r, tm), addend);
    upd(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r, addend);
    st[v] = max(st[v << 1], st[v << 1 | 1]);
  }
}

ll qry(int v, int tl, int tr, int l, int r) {
  if (l > r)
    return 0;
  if (l == tl && tr == r)
    return st[v];
  push(v);
  int tm = (tl + tr) >> 1;
  return max(qry(v << 1, tl, tm, l, min(r, tm)),
             qry(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r));
}

int jmp(int u, int k) {
  for (int i = 18; i >= 0; i--) {
    if (k & (1 << i)) {
      u = pa[u][i];
    }
  }
  return u;
}
int lca(int u, int v) {
  if (dep[u] < dep[v])
    swap(u, v);
  u = jmp(u, dep[u] - dep[v]);
  if (u == v)
    return u;
  for (int i = 18; i >= 0; i--) {
    if (pa[u][i] != pa[v][i]) {
      u = pa[u][i], v = pa[v][i];
    }
  }
  return pa[u][0];
}
void update1(int x, int y, ll val) {
  while (hld[x] != hld[y]) {
    upd(1, 1, n, in[hld[x]], in[x], val);
    x = pa[hld[x]][0];
  }
  upd(1, 1, n, in[y], in[x], val);
}

ll answer3(int u, int x) {
  ll ans = 0;
  while (hld[u] != hld[x]) {
    ans = max(ans, qry(1, 1, n, in[hld[u]], in[u]));
    u = pa[hld[u]][0];
  }
  return max(ans, qry(1, 1, n, in[x], in[u]));
}

vector<tuple<int, int, bool>> dec(int u, int v) {
  vector<tuple<int, int, bool>> pu, pv;
  while (top[u] != top[v]) {
    if (in[u] > in[v]) {
      swap(u, v);
    }
    ans = max(ans, st.get(in[top[v]], in[v]));
    v = par[top[v]];
  }
  if (in[u] > in[v])
    swap(u, v);
  ans = max(ans, st.get(in[u], in[v]));
  return ans;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie();
  cout.tie();
  cin >> n >> q;
  int op, u, v, x;
  ll val;
  for (int i = 1; i <= n - 1; i++) {
    cin >> u >> v;
    g[u].pb(v);
    g[v].pb(u);
  }
  dfs_size(1, 1);
  hld[1] = 1;
  dfs_hld(1, 1);
  while (q--) {
    cin >> op;
    if (op == 1) {
      assert(false);
      cin >> u >> v >> val;
      x = lca(u, v);
      update1(u, x, val);
      update1(v, x, val);
      upd(1, 1, n, in[x], in[x], -val);
    } else if (op == 2) {
      cin >> u >> val;
      upd(1, 1, n, in[u], in[u] + sz[u] - 1, val);
    } else if (op == 3) {
      cin >> u >> v;
      x = lca(u, v);
      cout << max(answer3(u, x), answer3(v, x)) << '\n';
    } else {
      cin >> u;
      cout << qry(1, 1, n, in[u], in[u] + sz[u] - 1) << '\n';
    }
  }
}
