#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define F first
#define S second
typedef long long ll;
typedef long double lf;
template <typename T>
using ordered_set = tree<ll, null_type, less<ll>, rb_tree_tag,
                         tree_order_statistics_node_update>;
const lf PI = acos(-1);
const string FNAME = "B";
const ll MOD = 1e9 + 7;
const lf EPS = 1e-6;

inline void A() {
  ll t;
  cin >> t;
  while (t--) {
    string s;
    ll n, k, sB = 0, cntA = 0, cntB = 0, res = INT_MAX;
    cin >> n >> k >> s;
    for (char ch : s) {
      sB += ch == 'B';
    }
    if (sB == k) {
      cout << "0\n";
    } else {
      cout << "1\n";
      for (ll i = 0; i < n; i++) {
        if (s[i] == 'A') {
          cntA++;
        } else {
          cntB++;
        }
        if (abs(sB - cntB) == k) {
          cout << i + 1 << " A\n";
          break;
        }
        if (abs(sB - cntB) + i + 1 == k) {
          cout << i + 1 << " B\n";
          break;
        }
      }
    }
  }
}

inline void B() {
  ll t;
  cin >> t;
  while (t--) {
    ll n, res = 0;
    cin >> n;
    vector<ll> a(n);
    for (ll &x : a) {
      cin >> x;
    }
    for (ll i = n - 2; i >= 0; i--) {
      if (a[i] > a[i + 1]) {
        ll cnt = a[i] / a[i + 1];
        if (!(a[i] % a[i + 1])) {
          res += cnt - 1;
          a[i] = a[i + 1];
        } else {
          res += cnt;
          //					a[i] -= a[i + 1] * (cnt - 1);
          a[i] /= cnt + 1;
        }
      }
      for (auto x : a) {
        cout << x << " ";
      }
      cout << '\n';
    }
    //	for (ll x: a) {
    //			cout << x << ' ';
    //		}
    cout << res << '\n';
  }
}
//	1 4 4 3 5 7 6
//	1 4 4 3 5 3 4 6
//	1 4 4 3 2 3 3 4 6
//	1 4 4 1 2 2 3 3 4 6
//	1 4 3 1 1 2 2 3 3 4 6
//	1 4 2 1 1 1 2 2 3 3 4 6
//	1 4 1 1 1 1 1 2 2 3 3 4 6
//	1 3 1 1 1 1 1 1 2 2 3 3 4 6
//	1 2 1 1 1 1 1 1 1 2 2 3 3 4 6
//	1 1 1 1 1 1 1 1 1 1 2 2 3 3 4 6

inline void C() {}

inline void D() {}

inline void E() {}

inline void F() {}

inline void G() {}

inline void H() {}

inline void I() {}

inline void J() {}

inline void K() {}

inline void L() {}

inline void M() {}

inline void N() {}

inline void O() {}

inline void P() {}

inline void Q() {}

inline void R() {}

inline void S() {}

inline void T() {}

inline void U() {}

inline void V() {}

inline void W() {}

inline void X() {}

inline void Y() {}

inline void Z() {}

int main(int argc, wchar_t **argv, wchar_t **envp) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  if (fopen((FNAME + ".INP").c_str(), "r")) {
    freopen((FNAME + ".INP").c_str(), "r", stdin);
    freopen((FNAME + ".OUT").c_str(), "w", stdout);
  }
  unordered_map<string, function<void()>> problem = {
      {"A", A}, {"B", B}, {"C", C}, {"D", D}, {"E", E}, {"F", F}, {"G", G},
      {"H", H}, {"I", I}, {"J", J}, {"K", K}, {"L", L}, {"M", M}, {"N", N},
      {"O", O}, {"P", P}, {"Q", Q}, {"R", R}, {"S", S}, {"T", T}, {"U", U},
      {"V", V}, {"W", W}, {"X", X}, {"Y", Y}, {"Z", Z}};
  problem[FNAME]();
  return EXIT_SUCCESS;
}
