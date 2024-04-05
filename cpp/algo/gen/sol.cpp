#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

#define sz(x) (int)x.size()
using i64 = long long;
const int LG = 30;

struct TRIE {
  struct node {
    int cnt, exist;
    node *child[2];
    node() {
      cnt = exist = 0;
      child[0] = child[1] = nullptr;
    }
  };

  node *root;
  void insert(int num) {
    node *p = root;
    for (int i = LG; ~i; i--) {
      int b = (num >> i & 1);
      if (p->child[b] == nullptr) {
        p->child[b] = new node();
      }
      p = p->child[b];
      p->cnt++;
    }
    p->exist++;
  }

  int64_t get(int num) {
    int64_t ans = 0;
    node *p = root;
    for (int i = LG; ~i; --i) {
      int b = (num >> i & 1);
      if (p->child[b ^ 1] != nullptr) {
        ans |= (1ll << b);
        p = p->child[b ^ 1];
      } else if (p->child[b] != nullptr) {
        p = p->child[b];
      } else {
        break;
      }
    }
    return ans;
  }

  bool find(int num) {
    node *p = root;
    for (int i = LG; ~i; i--) {
      int b = (num >> i & 1);
      if (p->child[b] == nullptr)
        return false;
      p = p->child[b];
    }
    return (p->exist != 0);
  }

  bool do_del(node *p, int num, int pos) {
    if (pos > -1) {
      int b = (num >> pos & 1);
      bool isC = do_del(p->child[b], num, pos - 1);
      if (isC)
        p->child[b] = nullptr;
    } else {
      p->exist--;
    }
    if (p != root) {
      p->cnt--;
      if (p->cnt == 0) {
        delete p;
        return true;
      }
    }
    return false;
  }

  void del(int num) {
    if (find(num)) {
      do_del(root, num, LG);
    }
  }
};

TRIE tr;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  vector<vector<int>> g(n + 1);
  for (int i = 0; i + 1 < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  vector<int> siz(n + 1), h(n + 1, -1), d(n + 1);
  auto dfs = [&](auto &sf, int u, int p) -> void {
    siz[u] = 1;
    d[u] = d[p] ^ a[u];
    for (int v : g[u]) {
      if (v != p) {
        sf(sf, v, u);
        siz[u] += siz[v];
        if (h[u] == -1 || siz[h[u]] < siz[v]) {
          h[u] = v;
        }
      }
    }
  };
  dfs(dfs, 1, 0);

  auto add = [&](auto &sf, int u, int p, int delt) -> void {
    if (delt == 1) {
      tr.insert(d[u]);
    } else
      tr.del(d[u]);
    for (int v : g[u]) {
      if (v != p) {
        sf(sf, v, u, delt);
      }
    }
  };

  int64_t ans = 0;
  auto sack = [&](auto &sf, int u, int p) -> void {
    int bg = h[u];
    for (int v : g[u]) {
      if (v != p && v != bg) {
        sf(sf, v, u);
        add(add, v, u, -1);
      }
    }
    if (~bg) {
      sf(sf, bg, u);
    }
    for (int v : g[u]) {
      if (v != p && v != bg) {
        add(add, v, u, 1);
      }
    }
    ans = max(ans, tr.get(d[u] ^ a[u]));
    tr.insert(d[u]);
  };
  sack(sack, 1, 0);

  cout << ans << '\n';
  // 1->2->3->4
  // 1->2
}

int32_t main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int TC = 1;
  // cin >> TC;
  while (TC--) {
    solve();
  }
}
