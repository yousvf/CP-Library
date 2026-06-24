struct SparseTable {
	vector<vector<int>> sp;
	SparseTable(vector<int>& v) {
		int n = v.size();
		sp = vector<vector<int>> (__lg(n) + 1, vector<int> (n));
		
		sp[0] = v;
		for(int mask = 1; (1 << mask) <= v.size(); mask++) {
			for(int i = 0; i + (1 << mask) <= v.size(); i++) {
				sp[mask][i] = merge(
					sp[mask - 1][i],
					sp[mask - 1][i + (1 << (mask - 1))]
				);
			}
		}
	}

	int merge(int a, int b) {
		return min(a, b);
	}

	int query(int l, int r) {
		int len = r - l + 1;
		int ret = INT_MAX;
		
		for(int mask = 0; l <= r; mask++) {
			if(len & (1 << mask)) {
				ret = merge(ret, sp[mask][l]);
				l += (1 << mask);
			}
		}
		
		return ret;
	}
	
	int query(int l, int r) {
		int len = r - l + 1;
		int lg = __lg(len);

		return merge(sp[lg][l], sp[lg][r - (1 << lg) + 1]);
	}
};
