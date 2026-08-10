int exp(int a, int b) {
	if(b <= 0) return 1;
	int ret = exp(a * a % MOD, b / 2);
	if(b % 2) ret = ret * a % MOD;
	return ret;
}

int gauss(vector<vector<int>> a, vector<int> &ans) {
	int n = a.size(), m = a[0].size() - 1;
	vector<int> pos(m, -1);
	int free_var = 0;
	const int MODSQ = MOD * MOD;
	int det = 1, rank = 0;

	for(int col = 0, row = 0; col < m && row < n; col++) {
		int mx = row;
		for(int k = row; k < n; k++) if(a[k][col] > a[mx][col]) mx = k;
		if(a[mx][col] == 0) {det = 0; continue;}
		for(int j = col; j <= m; j++) swap(a[mx][j], a[row][j]);
		if(row != mx) det = det == 0 ? 0 : MOD - det;
		det = det * a[row][col] % MOD;
		pos[col] = row;
		int inv = exp(a[row][col], MOD - 2);
		for(int i = 0; i < n && inv; i++) {
			if(i != row && a[i][col]) {
				int x = (a[i][col] * inv) % MOD;
				for(int j = col; j <= m && x; j++) {
					if(a[row][j]) a[i][j] = (MODSQ + a[i][j] - (a[row][j] * x)) % MOD;
				}
			}
		}

		row++; ++rank;
	}

	ans.assign(m, 0);
	for(int i = 0; i < m; i++){
		if(pos[i] == -1) free_var++;
		else ans[i] = (a[pos[i]][m] * exp(a[pos[i]][i], MOD - 2)) % MOD;
	}

	for(int i = 0; i < n; i++) {
		int val = 0;
		for(int j = 0; j < m; j++) val = (val + (ans[j] * a[i][j])) % MOD;
		if(val != a[i][m]) return -1; // no solution
	}

	return free_var; // has solution
}
