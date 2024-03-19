#include <bits/stdc++.h>
using namespace std;

int main() {
  long long x1, x2, v1, v2;
  cin >> x1 >> x2 >> v1 >> v2;
  if (v1 == v2) {
    cout << (x1 == x2 ? "0" : "-1");
  } else {
    long long tu = x2-x1;
    long long mau = v1-v2;
    long long g = __gcd(abs(tu), abs(mau));
    tu /= g;
    mau /= g;

    cout << fixed << setprecision(10) << tu*1.0l/mau;
  }
}