struct FenwickTree {
    int n;
    vector<int> bit;
    FenwickTree(int n) : n(n + 1), bit(n + 1) {}
	int query(int r) {
		int ret = 0;
		while(r > 0) {
			ret += bit[r];
			r -= (r & -r);	
		}

		return ret;
	}

	int query(int l, int r) {
		return query(r) - query(l - 1);
	}

	void update(int idx, int delta) {
		while(idx < N) {
			bit[idx] += delta;
			idx += (idx & -idx);
		}
	}

	int lowerbound(int val) {
		int sum = 0, pos = 0;
		for(int i = LOG; i >= 0; i--) {
			int x = pos + (1LL << i);
			if(x < N && sum + bit[x] < val) {
				sum += bit[x];
				pos += (1LL << i);
			}
		}

		return pos + 1;
	}
};