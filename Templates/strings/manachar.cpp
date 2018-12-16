namespace Manachar {

	int P[2 * N];
	string Q;
	//considering string of length N 
	string new_string(const string& s) {
		string NEW;
		// denotes the start of the string
		NEW += "@";
		NEW += "#";
		for(auto x: s) NEW += x, NEW += "#";
		// denotes the end of the string;
		NEW += "$";
		return NEW;
	}

	void lps(const string& s) {
		Q = new_string(s);
		int center = 0, right = 0;
		for(int i = 1; i < sz(Q) - 1; ++i) {
			// if the current index is in the right boundary, initialise with the mirror value of the current index in the actual string.
			if (i < right) P[i] = min(right - i, P[2 * center - i]);
			// Expand beyond the current length (if possible)
			while(Q[i + P[i] + 1] == Q[i - P[i] - 1]) ++P[i];
			// Update center, right if the current pallindrome expands beyond the right boundary.
			if (i + P[i] > right) center = i, right = i + P[i];
		}

		int maxlen = 0, palcenter = 0;
		for(int i = 1; i < sz(Q)-1; ++i) if (P[i] > maxlen) maxlen = P[i], palcenter = i;
		trace(maxlen, palcenter);
		// string pallindrome = s.substr((palcenter - 1 - maxlen) / 2, maxlen);
		// palcenter = palcenter / 2 - 1;
		return;
	}

	bool valid(int idx) {
		return !(Q[idx] == '#' | Q[idx] == '@' | Q[idx] == '$');
	}
}; 
