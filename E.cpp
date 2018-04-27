#include "bits/stdc++.h"
using namespace std;

const int mod = 1e9 + 7;
const int N = 1e5 + 5;

int n;
int arr[N];
int ans;
int tot;
vector < int > adj[N];
map < int , int > mp;
set < int > s;
int add = 0;

void solve(int u , int par) {
	bool notbefore = s.find(arr[u]) == s.end();
	s.insert(arr[u]);
	mp[arr[u]]--;
	bool added = false;
	if(notbefore and mp[arr[u]] > 0) {
		added = true;
		add += 1;
	}
	int others = (tot - (int) s.size()) + add;
	if((int) s.size() == others) {
		ans += 1;
	}
	for(int i = 0; i < adj[u].size(); ++i) {
		if(adj[u][i] != par) {
			solve(adj[u][i] , u);
		}
	}
	if(notbefore) {
		s.erase(arr[u]);
	}
	mp[arr[u]]++;
	if(added) {
		add--;
	}
}

int main() {
	cin >> n;
	for(int i = 1; i < n; ++i) {
		int u , v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i = 1; i <= n; ++i) {
		cin >> arr[i];
		mp[arr[i]]++;
	}
	tot = (int) mp.size();
	solve(1 , -1);
	cout << ans << endl;
	return 0;
}