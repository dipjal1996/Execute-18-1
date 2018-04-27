#include "bits/stdc++.h"
using namespace std;

const int mod = 1e9 + 7;
const int N = 1e5 + 5;

long long req[N] , ans[N];

int main() {
	int n , q;
	cin >> n >> q;
	for(int i = 1; i <= q; ++i) {
		int l , r , x;
		cin >> l >> r >> x;
		req[l] += x;
		req[r + 1] -= x;
	}
	for(int i = 1; i <= n; ++i) {
		req[i] += req[i - 1];
	}
	long long mx = -(long long) 1e18 , mn = (long long) 1e18;
	for(int i = 1; i <= n; ++i) {
		int x; cin >> x;
		ans[i] = (req[i] / x) + !!(req[i] % x);
		mx = max(mx , req[i]);
		mn = min(mn , req[i]);
	}
	for(int i = 1; i <= n; ++i) cout << ans[i] << " ";
	cout << endl;
	cout << mx << " " << mn << endl;
	return 0;
}