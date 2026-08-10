struct Manacher { // ! 0-indexed
	vector<int> p;
	void build(string &s) {
		string t;
		for(auto &val : s) t += '#', t += val;
		t += '#';
		int n = (int)t.size();
		p.resize(n, 1);
		int l = 1, r = 1;
		for(int i = 1; i < n; i++) {
			p[i] = max(0LL, min(r - i, p[l + r - i]));
			while(i - p[i] >= 0 && i + p[i] < n && t[i + p[i]] == t[i - p[i]]) p[i]++;
			if(p[i] + i > r) {
				r = i + p[i];
				l = i - p[i];
			}
		}
	}

	// even-len : center is left mid
	int GetLongest(int center, bool odd = true) {
		int NewCenter = 2 * center + !odd + 1;
		return p[NewCenter] - 1;
	}

	// return the longest palindrome
	// l and r : the range of the longest palindrome
	int GetLongest(int center, bool odd, int &l, int &r) {
		int NewCenter = 2 * center + !odd + 1;
		int len = p[NewCenter] - 1;
		
		l = center - len / 2 + !odd;
		r = center + len / 2;
		
		return len;
	}

	bool IsPalindrome(int l, int r) {
		return (r - l + 1) <= GetLongest((l + r) / 2 , l % 2 == r % 2);
	}
};
