#include <bits/stdc++.h>

using namespace std;

#ifdef LLOCAL
#include "algo/debug.cpp"
#else
#define debug(...) 42
#define debugArr(...) 42
#endif

using ll = long long;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vll = vector<ll>;

#define all(x) (x).begin(), (x).end()
#define isz(x) (int)(x).size()
#define rall (x).rbegin(), (x).rend()
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define fi first
#define se second

struct team {
  string name;
  int p = 0, g = 0, nog = 0;
};

void solve() {
  int n, k;
  cin >> n >> k;
  vector<team> vec(n);
  for (int i = 0; i < n; i++) {
    cin >> vec[i].name;
  }
  string teamAlice = vec[k - 1].name;
  for (int i = 0; i < n * (n - 1); i++) {
    string A, B;
    int sbtA, sbtB;
    cin >> A >> B >> sbtA >> sbtB;
    for (int j = 0; j < n; j++) {
      if (A == vec[j].name) {
        vec[j].g += sbtA - sbtB;
        vec[j].nog += sbtA;
        if (sbtA > sbtB) {
          vec[j].p += 3;
        } else if (sbtA == sbtB) {
          vec[j].p += 1;
        }
      }
      if (B == vec[j].name) {
        vec[j].g += sbtB - sbtA;
        vec[j].nog += sbtB;
        if (sbtB > sbtA) {
          vec[j].p += 3;
        } else if (sbtB == sbtA) {
          vec[j].p += 1;
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (vec[i].p < vec[j].p) {
        swap(vec[i], vec[j]);
      } else if (vec[i].p == vec[j].p) {
        if (vec[i].g < vec[j].g) {
          swap(vec[i], vec[j]);
        } else if (vec[i].g == vec[j].g) {
          if (vec[i].nog < vec[j].nog) {
            swap(vec[i], vec[j]);
          }
        }
      }
    }
  }

  int no = 1;
  for (int i = 0; i < n; i++) {
    cout << vec[i].name << " " << vec[i].p << " " << vec[i].g << " "
         << vec[i].nog << '\n';
  }
}
signed main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  solve();
  return 0;
}
