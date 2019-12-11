#define trace(...) {__f(#__VA_ARGS__, __VA_ARGS__);}
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
  cerr << name << " = " << arg1 << std::endl; }
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
  const char* comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << " = " << arg1<<" | ";__f(comma+1, args...); }
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; // OST: find_by_order, order_of_key
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#pragma GCC optimize("Ofast")
optimize("unroll-loops")
target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

//https://codeforces.com/blog/entry/60737
//gp_hash_table has far superior performance for insertions/deletions, while cc has marginally better performance for reads/writes
gp_hash_table<int, int> table;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
gp_hash_table<key, int, chash> table;
