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

  for (int i = 0; i < 26; i++) {
    for (int j = i; j < 26; j++) {
      for (int k = j; k < 26; k++) {
        if (i + j + k + 3 == n) {
          cout << (char)('a' + i);
          cout << (char)('a' + j);
          cout << (char)('a' + k);
          cout << '\n';
          return;
        }
      }
    }
  }
}

int32_t main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int TC = 1;
  cin >> TC;
  while (TC--) {
    solve();
  }
}
