#define trace(...) {cerr << ">> ", __f(#__VA_ARGS__, __VA_ARGS__);}
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
  cerr << name << " = " << arg1 << std::endl; }
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
  const char* comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << " = " << arg1<<" | ";__f(comma+1, args...); }

// OST: find_by_order, order_of_key
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// compiler options: -Wall -std=c++11 -g [-O2-Wno-reorder]
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")

// arora
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