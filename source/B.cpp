#include "bits/stdc++.h"
using namespace std;

const int mod = 1e9 + 7;
const int N = 1e5 + 5;

int arr[N];
int lf[N];

int main() {
	lf[1] = 1;
	for(int i = 2; i < N; ++i) {
		for(int j = i; j < N; j += i) 
			lf[j] = i;
	}
	int tt;
	cin >> tt;
	while(tt--) {
		int n;
		cin >> n;
		for(int i = 1; i <= n; ++i) cin >> arr[i];
		bool zero = false;
		for(int i = 1; i <= n; ++i) {
			if(arr[i] == 0) {
				zero = true;
				break;
			}
		}
		if(zero) {
			cout << -1 << endl;
		}
		long long ans = 0;
		int prev = -1;
		for(int i = 1; i <= n; ++i) {
			int val = lf[abs(arr[i])];
			if(val > prev) {
				ans += val;
			}
			prev = val;
		}
		cout << ans << endl;
	}
	return 0;
}