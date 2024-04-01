#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  for (int i = 1; i <= 10; i++) {
    startTest(i);
    cout << rnd.next(10) << " ";
  }
  return 0;
}
