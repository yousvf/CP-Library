class Fenwick2D {
private:
	const int n, m;
	vector<vector<int>> bit;

public:
	Fenwick2D(int n, int m) : n(n), m(m), bit(n + 1, vector<int> (m + 1)) {}

	void add(int r, int c, int val) {
		r++, c++;
		for(; r <= n; r += r & -r) {
			for(int i = c; i <= m; i += i & -i) { bit[r][i] += val; }
		}
	}

	int query(int r, int c) {
		r++, c++;
		int sum = 0;
		for(; r > 0; r -= r & -r) {
			for(int i = c; i > 0; i -= i & -i) { sum += bit[r][i]; }
		}

		return sum;
	}

	int query(int r1, int c1, int r2, int c2) {
		return query(r2, c2) - query(r2, c1 - 1) - query(r1 - 1, c2) + query(r1 - 1, c1 - 1);
	}
};
