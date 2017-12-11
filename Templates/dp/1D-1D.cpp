Quadrangular Inequality : C[a][c] + C[b][d] <= C[a][d] + C[b][c] with a <= b <= c <= d.
Applicable where A[i] <= A[i + 1] <= ...... (A[i] is best position to calculate DP for i)
(Quadrangular Inequality holds)
Usage: Initialise DP[1], arr.push_back({N + 1, 1}) and get(x, y) is cost for segment from x...y

for each i:
	insert(i);
	int pos = lower_bound(arr.begin(), arr.end(), make_pair(i, 0ll)) - arr.begin();
	pos = arr[pos].second;
	dp[i] = get(pos, i);

void insert(int idx){
	while(true){
		if(arr.size() > 1){
			auto X = arr[arr.size() - 1], Y = arr[arr.size() - 2];
			int L = 1, H = N + 1, LL = 1, HH = N + 1;
			while(L < H){
				int mid = (L + H) >> 1;
				if(get(Y.second, mid) <= get(X.second, mid)) L = mid + 1;
				else H = mid;
			}
			while(LL < HH){
				int mid = (LL + HH) >> 1;
				if(get(X.second, mid) <= get(idx, mid)) LL = mid + 1;
				else HH = mid;
			}
			if(L > LL){
				arr.pop_back();
				continue;
			}
			else break;
		}
		else break;
	}
	auto X = arr[arr.size() - 1];
	int L = idx, H = N + 1;
	while(L < H){
		int mid = (L + H) >> 1;
		if(get(X.second, mid) <= get(idx, mid)) L = mid + 1;
		else H = mid;
	}
	if(L > N) return;
	else{
		arr[arr.size() - 1].first = L - 1;
		arr.push_back({N + 1, idx});
	}
}