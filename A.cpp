#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
int main() {
int a , b;
cin >> a >> b;
if(b == 0) {
cout << '/' << endl;
return 0;
}
int mul = a * b;
int add = a + b;
int minus = a - b;
int divide = a / b;
int mx = max(max(mul , add) , max(minus , divide));
if(mx == mul) {
cout << "*" << endl;
} else if(mx == add) {
cout << "+" << endl;
} else if(mx == minus) {
cout << "-" << endl;
} else {
cout << "/" << endl;
}
return 0;
}
