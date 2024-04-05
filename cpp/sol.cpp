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

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
    }
  }

  filesystem(int);
}

int32_t main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int TC = 1;
  // cin >> TC;
  while (TC--) {
    solve();
  }
}
