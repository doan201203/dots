#include <bits/stdc++.h>
using namespace std;

template <class T, auto e, auto fun> class segtree {
public:
  int n;
  vector<T> tree;
  segtree(int nn) : n(nn) { tree.assign(n << 1 | 1, e()); }

  void modify(int x, int l, int r, int ll, int rr, T v) {
    if (l >= ll && r <= rr) {
    }
  }
};
