
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
const int M = 1 << 10;
int64_t dp[20][M][5][2];
string s;

int64_t f(int pos, int msk, int sum, int lw, int zr) {
  if (pos < 0) {
    return !sum;
  }
  if (lw && ~dp[pos][msk][sum][zr]) {
    return dp[pos][msk][sum][zr];
  }
  int LMT = 9;
  if (!lw)
    LMT = s[pos] - '0';
  int64_t ans = 0;
  for (int i = 0; i <= LMT; i++) {
    int nmsk = msk;
    if (zr) {
      if (nmsk >> i & 1)
        continue;
      else
        nmsk |= (1 << i);
    }
    ans +=
        f(pos - 1, nmsk, (sum * 10 + i) % 5, lw || (i < LMT), zr || (i != 0));
  }

  return (lw ? dp[pos][msk][sum][zr] = ans : ans);
}

void solve() {
  memset(dp, -1, sizeof dp);
  cin >> s;
  reverse(s.begin(), s.end());
  cout << f(sz(s) - 1, 0, 0, 0, 0) - 1 << '\n';
}

int32_t main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int TC = 1;
  // cin >> TC;
  while (TC--) {
    solve();
  }
}
