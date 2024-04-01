#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

#define int int64_t
#define sz(x) (int)x.size()
using i64 = long long;

const int N = 1003;

const int dx[] = {0, -1, 0, 1, 1, 1, -1, -1};
const int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c; cin >> c;
      if (c != '.')
        a[i - 1][j - 1] = c - '0';
    }
  }
  
  int ans = 0;
  while (1) {
    bool ok = false;
    //check full .
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (a[i][j] != 0) {
          ok = true;
        }
      }
    }
    if (!ok) { break; }
    auto nxt = a;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int cnt = 0;
        for (int k = 0; k < 8; k++) {
          int x = i + dx[k];
          int y = j + dy[k];
          if (x < 0 || x >= n || y < 0 || y >= m) {
            continue;
          }
          if (a[x][y] == 0) {
            cnt++;
          }
        }
        if (cnt >= a[i][j]) {
          nxt[i][j] = 0;
        }
      }
    }
    if (nxt == a) {
      break;
    }
    ans++;
    nxt.swap(a);
    // debug(a);
  }

  cout << ans << '\n';
}

int32_t main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int TC = 1;
  // freopen("in", "r", stdin);
  // cin >> TC;
  while (TC--) {
    solve();
  }
}
