#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5;
ll MOD;
ll p[N + 1];

struct node {
  ll res;
  int l;
  int r;
};

node gan(ll x, int y, int z) {
  node res;
  res.res = x;
  res.l = y;
  res.r = z;
  return res;
}

node tree[4 * N];
string s;

void mod() {
  long long res = 1;
  p[0] = 1;
  for (int i = 1; i <= N; i++) {
    p[i] = (res * 31) % MOD;
    res *= 31;
    res %= MOD;
  };
};

node merge(node a, node b) {
  if (a.l == -1)
    return b;
  if (b.l == -1)
    return a;

  node res;
  int temp = b.r - b.l + 1;
  res.res = (a.res % MOD * p[temp] % MOD) % MOD + b.res;
  res.res %= MOD;
  res.l = a.l;
  res.r = b.r;

  return res;
}

void buildtree(int id, int l, int r) {
  if (l > r)
    return;
  if (l == r) {
    tree[id].res = s[l] - 'a' + 1;
    tree[id].l = tree[id].r = l;
    return;
  };

  int mid = (l + r) / 2;
  buildtree(id * 2, l, mid);
  buildtree(id * 2 + 1, mid + 1, r);

  tree[id] = merge(tree[id * 2], tree[id * 2 + 1]);
  // cerr<<l<<" "<<r<<" "<<tree[id]<<'\n';
};

node inf = gan(-1, -1, -1);

node get(int id, int l, int r, int u, int v) {
  // cerr<<l<<" "<<r<<'\n';
  if (l > v || r < u || l > r) {
    // cerr << '\n';
    return inf;
  }
  if (u <= l && r <= v) {
    // cerr<<tree[id]<<'\n';
    return tree[id];
  };

  int mid = (l + r) / 2;

  node temp =
      merge(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));

  return temp;
}

void update(int id, int l, int r, int u, char t) {
  if (l > u || r < u || l > r) {
    return;
  };
  if (l == r) {
    s[l] = t;
    tree[id].res = s[l] - 'a' + 1;
    return;
  };

  int mid = (l + r) / 2;
  update(id * 2, l, mid, u, t);
  update(id * 2 + 1, mid + 1, r, u, t);

  tree[id] = merge(tree[id * 2], tree[id * 2 + 1]);
}

int main() {
  // freopen("A.INP", "r", stdin);
  // freopen("A.out", "w", stdout);

  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> s;
  cin >> MOD;
  mod();

  int n = s.length();
  s = ' ' + s;

  // cout<<merge(1, 5, 1088, 50);
  buildtree(1, 1, n);
  int q;
  cin >> q;

  for (int i = 1; i <= q; i++) {
    char t;
    int x;
    cin >> t >> x;
    if (t == '?') {
      int y;
      cin >> y;
      cout << (get(1, 1, n, x, y).res % MOD) << '\n';
    } else {
      char temp;
      cin >> temp;
      update(1, 1, n, x, temp);
    };
  };

  return 0;
}
