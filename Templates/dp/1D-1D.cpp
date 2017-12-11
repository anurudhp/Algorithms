// http://www.spoj.com/submit/ACQUIRE/id=17751232

#include<bits/stdc++.h>
#define int long long int
using namespace std;
const int MAXN = 1e5 + 5;
int N, dp[MAXN];
pair<int,int> A[MAXN];
vector<pair<int,int> >v, w, arr;

int calculate(int pos, int choose){
	return dp[choose - 1] + (A[pos].second * A[choose].first);
}

void insert(int pos, int val){
	
	while(true){

		if(arr.size() == 1){
			int _pos = arr[0].first;
			int _val = arr[0].second;
			_pos = pos - 1;
			arr.pop_back();
			if(_pos) arr.push_back({_pos, _val});
			arr.push_back({MAXN, val});
			break;
		}

		int sz = arr.size();
		int _pos = arr[sz - 1].first;
		int _val = arr[sz - 1].second;

		int __pos = arr[sz - 2].first;
		int __val = arr[sz - 2].second;

		arr.pop_back();
		arr.pop_back();

		if(pos > __pos && pos <= _pos){
			arr.push_back({__pos, __val});
			_pos = pos - 1;
			if(_pos) arr.push_back({_pos, _val});
			arr.push_back({MAXN, val});
			break;
		}

		else arr.push_back({__pos, __val});		
	}

	assert(arr[arr.size() - 1].first == MAXN);
}

signed main(){

	ios::sync_with_stdio(false);

	cin >> N;

	for(int i=1; i<=N; ++i){
		int x, y;
		cin >> x >> y;
		v.push_back({x, y});
	}
	
	sort(v.rbegin(), v.rend());

	w.push_back({v[0].first, v[0].second});
	for(int i=1; i<v.size(); ++i){
		if(v[i].second <= w[w.size() - 1].second) continue;
		w.push_back({v[i].first, v[i].second});
	}

	for(int i=1; i<=w.size(); ++i) A[i].first = w[i-1].first, A[i].second = w[i-1].second;
	N = w.size();
	
	dp[1] = A[1].first * A[1].second;
	arr.push_back({MAXN, 1});

	// (x, y) min arr means use y till xth index

	for(int i=2; i<=N; ++i){

		int pos = lower_bound(arr.begin(), arr.end(), make_pair(i, 0ll)) - arr.begin();
		pos = arr[pos].second;
		dp[i] = dp[pos - 1] + (A[pos].first * A[i].second);
		dp[i] = min(dp[i], dp[i-1] + (A[i].first * A[i].second));

		if(i == N) break;

		// Find max such that we can use i till that index
		int low = i+1, high = N + 1;
		while(low < high){
			int mid = low + high;
			mid >>= 1;

			int pos = lower_bound(arr.begin(), arr.end(), make_pair(mid, 0ll)) - arr.begin();
			pos = arr[pos].second;

			if(calculate(mid, pos) > calculate(mid, i)){
				high = mid;
			}
			else{
				low = mid + 1;
			}

		}
		insert(low, i);
	}

	cout << dp[N];

}
