vector<vector<int>> automaton(string &s) {
	int n = s.length();
	vector<vector<int>> nxt(n, vector<int> (26));
	for(int i = 0; i < n; i++) {
		for(int c = 0; c < 26; c++) {
			if(i && 'a' + c != s[i]) nxt[i][c] = nxt[pi[i - 1]][c];
			else nxt[i][c] = i + ('a' + c == s[i]);
		}
	}

	return nxt;
}
