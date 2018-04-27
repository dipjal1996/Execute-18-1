#include "bits/stdc++.h"
using namespace std;

const int mod = 1e9 + 7;
const int N = 1e6 + 6;

int n , m;
int mat[505][505];
int uf[N];
int val[N];

int FIND(int u) {
	if(uf[uf[u]] != uf[u]) {
		return uf[u] = FIND(uf[u]);
	}
	return uf[u];
}

void join(int u , int v) {
	u = FIND(u) , v = FIND(v);
	if(val[u] >= val[v]) {
		uf[v] = u;
	} else {
		uf[u] = v;
	}
}

int getId(int x, int y) {
	return ((x - 1) * m) + y;
}

int dx[] = {-1, 1 , 0 , 0};
int dy[] = {0 , 0 , -1 , 1};

int main() {
	cin >> m >> n;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			cin >> mat[i][j];
		}
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			bool yes = false;
			for(int dir = 0; dir < 4; ++dir) {
				int newx = i + dx[dir];
				int newy = j + dy[dir];
				if(newx >= 1 and newx <= n and newy >= 1 and newy <= m) {
					yes |= mat[newx][newy] < mat[i][j];
				}
			}
			uf[getId(i , j)] = getId(i , j);
			val[getId(i , j)] = yes;
		}
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			for(int dir = 0; dir < 4; ++dir) {
				int newx = i + dx[dir];
				int newy = j + dy[dir];
				if(newx >= 1 and newx <= n and newy >= 1 and newy <= m and mat[newx][newy] == mat[i][j]) {
					join(getId(i , j) , getId(newx , newy));
				}
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			int root = FIND(getId(i , j));
			if(!val[root]) ans++;
		}
	}
	cout << ans << endl;
	return 0;
}