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
  int ans = 0;
  vector<int> a;
  for (int i = 1; i <= n; i++) {
    string s = to_string(i);
    set<char> st;
    for (char j : s)
      st.insert(j);
    if (i % 5 == 0 && sz(s) == sz(st))
      ++ans, a.push_back(i);
  }
  // for (int i : a)
  // cout << i << " ";
  cout << ans;
}

int32_t main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int TC = 1;
  // cin >> TC;
  while (TC--) {
    solve();
  }
}
