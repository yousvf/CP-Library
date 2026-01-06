struct Hash {
	const int base1 = 127, base2 = 131, mod1 = MOD, mod2 = 2e9 + 11;

	int n;
	vector<int> pw1, pw2;
	vector<pair<int, int>> pre, suf;

	Hash(const string &s) {
		n = s.size();

		pw1.assign(n + 1, 1);
		pw2.assign(n + 1, 1);
		for(int i = 1; i <= n; i++) {
			pw1[i] = (pw1[i - 1] * base1) % mod1;
			pw2[i] = (pw2[i - 1] * base2) % mod2;
		}

		pre.assign(n + 1, {0, 0});
		suf.assign(n + 1, {0, 0});
		for(int i = 1; i <= n; i++) {
			pre[i].first  = (pre[i - 1].first  * base1 + s[i - 1]) % mod1;
			pre[i].second = (pre[i - 1].second * base2 + s[i - 1]) % mod2;
			suf[i].first  = (suf[i - 1].first  * base1 + s[n - i]) % mod1;
			suf[i].second = (suf[i - 1].second * base2 + s[n - i]) % mod2;
		}
	}

	pair<int, int> get(int l, int r, const vector<pair<int, int>> &h) {
		l++, r++;
		int x1 = (h[r].first  - h[l - 1].first  * pw1[r - l + 1]) % mod1;
		int x2 = (h[r].second - h[l - 1].second * pw2[r - l + 1]) % mod2;
		if(x1 < 0) x1 += mod1;
		if(x2 < 0) x2 += mod2;
		return {x1, x2};
	}
	
	bool isPalindrome(int l, int r) {
		return get(l, r, pre) == get(n - r + 1, n - l + 1, suf);
	}
};