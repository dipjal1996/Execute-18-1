#include "bits/stdc++.h"
using namespace std;const int mod = 1e9 + 7;
int add(int a , int b) {
a += b;
if(a >= mod) {
a -= mod;
}
return a;
}
int mul(int a , int b) {
return (1LL * (a % mod) * (b % mod)) % mod;
}
int power(int a , int b) {
int res = 1;
while(b > 0) {
if(b & 1) res = mul(res , a);
a = mul(a , a);
b /= 2;
}
return res;
}
int invmd(int a) {
return power(a , mod - 2);
}
int pw2[1000055];
int main() {
int n;
cin >> n;
string s;
cin >> s;
pw2[0] = 1;
for(int i = 1; i <= n + 5; ++i) {
pw2[i] = mul(pw2[i - 1] , 2);
}
int xxes = 0;
int ans = 0;
for(int i = 0; i < n; ++i) {
if(s[i] == 'x') {
xxes = add(xxes , invmd(pw2[i + 1]));
} else {
ans = add(ans , mul(pw2[i] , xxes));
}
}cout << ans << endl;
return 0;
}
