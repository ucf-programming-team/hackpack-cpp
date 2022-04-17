// This file is the driver for all of the .test.cpp files in tests/, 
// for use with the verifier CI. 
#include <bits/stdc++.h>
using namespace std;
#define sz(x) int(size(x))
#define rep(a,b,c) for (int a = (b); a < (c); a++)
#define all(x) begin(x),end(x)
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

void test();

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    test();

    return 0;
}
