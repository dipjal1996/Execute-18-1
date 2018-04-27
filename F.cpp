#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
const int N = 1e5 + 5;
int dp[N][7];
map < char , int > mp;
int main() {
string str = "epsilon";
for(int i = 0; i < 7; ++i) mp[str[i]] = i;
int tt;
cin >> tt;
while(tt--) {
string s;
cin >> s;
int n = (int) s.size();
memset(dp , 0 , sizeof dp);
if(s[0] == 'e') dp[0][0] = 1;
for(int i = 1; i < n; ++i) {
for(int j = 0; j < 7; ++j) dp[i][j] = dp[i - 1][j];
if(s[i] == 'e') dp[i][0]++;
for(int j = 1; j < 7; ++j) {
if(mp[s[i]] == j) {
if(dp[i - 1][j - 1] > 0) {
dp[i][j] = max(dp[i][j] , dp[i - 1][j - 1] + 1);
}
if(dp[i - 1][j] > 0) {
dp[i][j] = max(dp[i][j] , dp[i - 1][j] + 1);
}
}
}
}
if(!dp[n - 1][6]) cout << -1 << endl;
else cout << dp[n - 1][6] << endl;
}
return 0;
}
