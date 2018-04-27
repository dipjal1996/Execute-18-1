#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
const int N = 1e5 + 5;
int uf[N];
int loop;
int FIND(int u) {
if(uf[uf[u]] != uf[u]) {
return uf[u] = FIND(uf[u]);
}
return uf[u];
}
bool join(int u , int v) {
u = FIND(u) , v = FIND(v);
if(u != v) {
uf[u] = v;
return false;
} else {
loop++;
return true;
}
return true;
}
pair < int , int > edges[N];
int main() {
int n , m;
cin >> n >> m;
int pt = -1;
for(int i = 1; i <= n; ++i) uf[i] = i;
for(int i = 1; i <= m; ++i) {
int u , v;
cin >> u >> v;edges[i] = make_pair(u , v);
if(join(u , v)) {
pt = i;
}
}
set < int > roots;
for(int i = 1; i <= n; ++i) {
if(FIND(i) == i) {
roots.insert(i);
}
}
bool yes = ((int) (roots.size()) == 1) and (loop == 1);
if(!yes) {
cout << "NO" << endl;
return 0;
}
set < int > s;
int u = edges[pt].first;
int v = edges[pt].second;
s.insert(u);
s.insert(v);
for(int i = pt - 1; i >= 1; --i) {
if(edges[i].first == u or edges[i].second == u) {
if(edges[i].first == u) u = edges[i].second;
if(edges[i].second == u) u = edges[i].first;
}
if(edges[i].first == v or edges[i].second == v) {
if(edges[i].first == v) v = edges[i].second;
if(edges[i].second == v) v = edges[i].first;
}
s.insert(u);
s.insert(v);
if(u == v) break;
}
for(set < int > :: iterator it = s.begin(); it != s.end(); ++it) cout << *it << " ";
cout << endl;
return 0;
}
