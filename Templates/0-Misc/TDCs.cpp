// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define LL					long long
#define db 					long double
#define ii 					pair <int, int>
#define fi 					first
#define se 					second
#define sz(a) 				(int) a.size()
#define all(a) 				a.begin(), a.end()
#define rep(i, a, b) 		for (int i = a; i < b; ++i)
#define repv(i, a, b) 		for (int i = b - 1; i >= a; --i)
#define SET(A, val) 		memset(A, val, sizeof(A))

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
	template <typename Arg1>
	void __f(const char* name, Arg1&& arg1){
		cerr << name << " : " << arg1 << endl;
	}
	template <typename Arg1, typename... Args>
	void __f(const char* names, Arg1&& arg1, Args&&... args){
		const char* comma = strchr(names + 1, ','); 
		cerr.write(names, comma - names) << " : " << arg1 << " | ";
		__f(comma + 1, args...);
	}
#else
#define trace(...)
#endif

template <typename T>
T gcd(T a, T b) { 
	return (b == 0) ? a: gcd(b, a % b); 
} 

int main() {
	ios::sync_with_stdio (false);
	cin.tie(NULL); cout.tie(NULL);
	return 0;
}























