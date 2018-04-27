#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 5;

int n;
int arr[N];
int tin[N];
int tout[N];
int val[N];
int val5[N];
int timer;
int subsize[N];
vector < int > adj[N];

pair < int , int > factorize(int x) {
  int twos = 0 , fives = 0;
  while(x % 2 == 0) {
  	twos++;
  	x /= 2;
  }
  while(x % 5 == 0) {
  	fives++;
  	x /= 5;
  }
  return make_pair(twos , fives);
}

void dfs(int u, int par) {
	subsize[u] = 1;
	tin[u] = ++timer;
	pair < int , int > pp = factorize(arr[u]);
	val[timer] = pp.first;
	val5[timer] = pp.second;
	for(int i = 0; i < adj[u].size(); ++i) {
		if(adj[u][i] != par) {
			dfs(adj[u][i] , u);
			subsize[u] += subsize[adj[u][i]];
		}
	}
	tout[u] = timer;
}

int segtree[N << 2];
int segtree5[N << 2];
int pt[N << 2];
int pt5[N << 2];

void build(int node , int u , int v) {
  if(u > v) return;
  if(u == v) {
  	segtree[node] = val[u];
  	segtree5[node] = val5[u];
  	pt[node] = pt5[node] = u;
  	return;
  }
  int m = (u + v) / 2;
  build(node * 2 , u , m);
  build(1 + (node * 2) , m + 1 , v);
  if(segtree[node * 2] < segtree[1 + (node * 2)]) {
  	segtree[node] = segtree[node * 2];
  	pt[node] = pt[node * 2];
  } else {
  	segtree[node] = segtree[1 + (node * 2)];
  	pt[node] = pt[1 + (node * 2)];
  }
  if(segtree5[node * 2] < segtree5[1 + (node * 2)]) {
  	segtree5[node] = segtree5[node * 2];
  	pt5[node] = pt5[node * 2];
  } else {
  	segtree5[node] = segtree5[1 + (node * 2)];
  	pt5[node] = pt5[1 + (node * 2)];
  }
}

pair < int , int > query(int node , int u , int v , int l , int r) {
	if(u > v | u > r | v < l) return make_pair((int) 1e7 , 0);
	if(u >= l and v <= r) return make_pair(segtree[node] , pt[node]);
	int m = (u + v) / 2;
	pair < int , int > q1 = query(node * 2 , u , m , l , r);
	pair < int , int > q2 = query(1 + (node * 2) , m + 1 , v , l , r);
	if(q1.first < q2.first) return q1;
	return q2;
}

pair < int , int > query5(int node , int u , int v , int l , int r) {
	if(u > v | u > r | v < l) return make_pair((int) 1e7 , 0);
	if(u >= l and v <= r) return make_pair(segtree5[node] , pt5[node]);
	int m = (u + v) / 2;
	pair < int , int > q1 = query5(node * 2 , u , m , l , r);
	pair < int , int > q2 = query5(1 + (node * 2) , m + 1 , v , l , r);
	if(q1.first < q2.first) return q1;
	return q2;
}

void update(int node , int u , int v,  int idx , int val) {
	if(u > v | u > idx | v < idx) return;
	if(u >= idx and v <= idx) {
		segtree[node] = val;
		return;
	}
	int m = (u + v) / 2;
	update(node * 2 , u , m , idx , val);
	update(1 + (node * 2) , m + 1 , v , idx , val);
	if(segtree[node * 2] < segtree[1 + (node * 2)]) {
  		segtree[node] = segtree[node * 2];
  		pt[node] = pt[node * 2];
  	} else {
  		segtree[node] = segtree[1 + (node * 2)];
  		pt[node] = pt[1 + (node * 2)];
  	}
}

void update5(int node , int u , int v,  int idx , int val) {
	if(u > v | u > idx | v < idx) return;
	if(u >= idx and v <= idx) {
		segtree5[node] = val;
		return;
	}
	int m = (u + v) / 2;
	update5(node * 2 , u , m , idx , val);
	update5(1 + (node * 2) , m + 1 , v , idx , val);
	if(segtree5[node * 2] < segtree5[1 + (node * 2)]) {
  		segtree5[node] = segtree5[node * 2];
  		pt5[node] = pt5[node * 2];
  	} else {
  		segtree5[node] = segtree5[1 + (node * 2)];
  		pt5[node] = pt5[1 + (node * 2)];
  	}
}


int main() {
  scanf("%d" , &n);
  for(int i = 1; i < n; ++i) {
  	int u , v;
  	scanf("%d %d" , &u , &v);
  	adj[u].push_back(v);
  	adj[v].push_back(u);
  }
  for(int i = 1; i <= n; ++i) {
  	scanf("%d" , arr + i);
  }
  timer = 0;
  dfs(1 , -1);
  build(1 , 1 , n);
  int q;
  scanf("%d" , &q);
  while(q--) {
  	int typ , u;
  	scanf("%d %d" , &typ , &u);
  	if(!typ) {
  		if(subsize[u] < 2) {
  			printf("-1\n");
  		} else {
  		    pair < int , int > pp = query(1 , 1 , n , tin[u] , tout[u]);
  		    int val = pp.first;
  		    int idx = pp.second;
  		    update(1 , 1 , n , idx , (int) 1e7);
  		    int cur2 = val + query(1 , 1 , n , tin[u] , tout[u]).first;
  		    update(1 , 1 , n , idx , val);
  		    pp = query5(1 , 1 , n , tin[u] , tout[u]);
  		    val = pp.first;
  		    idx = pp.second;
  		    update5(1 , 1 , n , idx , (int) 1e7);
  		    int cur5 = val + query5(1 , 1 , n , tin[u] , tout[u]).first;
  		    update5(1 , 1 , n , idx , val);
  		    printf("%d\n" , min(cur2 , cur5));
  		}
  	} else {
  		if((n - subsize[u] + 1) < 2) {
  			printf("-1\n");
  		} else {
  			vector <int> twos;
  			pair < int , int > pp = query(1 , 1 , n , 1 , tin[u]);
  			int val = pp.first;
  			int idx = pp.second;
  			twos.push_back(val);
  			if(val != (int) 1e7) {
  				update(1 , 1 , n , idx , (int) 1e7);
  				twos.push_back(query(1 , 1 , n , 1 , tin[u]).first);
  				update(1 , 1 , n , idx , val);
  			}
  			pp = query(1 , 1 , n , tout[u] + 1 , n);
  			val = pp.first;
  			idx = pp.second;
  			twos.push_back(val);
  			if(val != (int) 1e7) {
  				assert(idx > 0);
  				update(1 , 1 , n , idx , (int) 1e7);
  				twos.push_back(query(1 , 1 , n , tout[u] + 1 , n).first);
  				update(1 , 1 , n , idx , val);
  			}
  			sort(twos.begin() , twos.end());
  			assert(twos.size() >= 2);
  			long long cur2 = 1LL * (twos[0] + twos[1]);
  			vector <int> fives;
  			pp = query5(1 , 1 , n , 1 , tin[u]);
  			val = pp.first;
  			idx = pp.second;
  			fives.push_back(val);
  			if(val != (int) 1e7) {
  				update5(1 , 1 , n , idx , (int) 1e7);
  				fives.push_back(query5(1 , 1 , n , 1 , tin[u]).first);
  				update5(1 , 1 , n , idx , val);
  			}
  			pp = query5(1 , 1 , n , tout[u] + 1 , n);
  			val = pp.first;
  			idx = pp.second;
  			fives.push_back(val);
  			if(val != (int) 1e7) {
  				update5(1 , 1 , n , idx , (int) 1e7);
  				fives.push_back(query5(1 , 1 , n , tout[u] + 1 , n).first);
  				update5(1 , 1 , n , idx , val);
  			}
  			sort(fives.begin() , fives.end());
  			assert(fives.size() >= 2);
  			long long cur5 = 1LL * (fives[0] + fives[1]);
  			assert(min(cur2 , cur5) != (int) 1e7);
  			printf("%lld\n" , min(cur2 , cur5));
  		}
  	}
  }
  return 0;
}