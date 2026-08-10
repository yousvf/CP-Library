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

vector<int> kmp(string& s, string& p, vector<int>& pi) {
	vector<int> ret;
	int n = s.length(), m = p.length();
	int j = 0;
	for(int i = 0; i < n; i++) {
		while(j && s[i] != p[j]) j = pi[j - 1];
		j += (s[i] == p[j]);
		if(j == m) {
			ret.push_back(i - j + 2);
			j = pi[j - 1];
		}
	}

	return ret;
}
