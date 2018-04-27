#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
const int N = 1e5 + 5;
int ans_typ_1[N], ans_typ_2[26][N];
int main() {
string s;
cin >> s;
int n = (int) s.size();
for(int i = 0; i < n; ++i) {
for(int j = 0; j < 26; ++j) {
ans_typ_2[j][i] = ans_typ_2[j][i - 1];
}
ans_typ_2[(int) (s[i] - 'a')][i]++;
int mn = -1;
int pt = -1;
for(int j = 0; j < 26; ++j) {
if(ans_typ_2[j][i] > mn) {
mn = ans_typ_2[j][i];
pt = j;
}
}
ans_typ_1[i] = pt;
}
int q;
cin >> q;
while(q--) {
int typ , x;
cin >> typ >> x;
if(typ == 1) {
cout << ((char) (ans_typ_1[x] + 'a')) << endl;
} else {
char c;
cin >> c;
int r = (int) (c - 'a');
int val = ans_typ_2[r][x];
if(!val) {
val = -1;
}
cout << val << endl;
}
}
return 0;}
