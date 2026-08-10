vector<int> build(string& p) {
	int n = p.length();
	vector<int> pi(n);
	for(int i = 1; i < n; i++) {
		int j = pi[i - 1];
		while(j && p[i] != p[j]) j = pi[j - 1];
		pi[i] = j + (p[i] == p[j]);
	}

	return pi;
}
