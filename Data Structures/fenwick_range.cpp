struct FenwickTree {
	int n;
    vector<int> bit1, bit2;
    FenwickTree(int n) : n(n + 1), bit1(n + 1), bit2(n + 1) {}
	
	int query(int r, vector<int>& tree) {
		int ret = 0;
		while(r > 0) {
			ret += tree[r];
			r -= (r & -r);	
		}

		return ret;
	}

	int query(int idx) {
		return query(idx, bit1) * idx - query(idx, bit2);
	}

	int query(int l, int r) {
		return query(r) - query(l - 1);
	}

	void update(int idx, int delta, vector<int>& tree) {
		while(idx < n) {
			tree[idx] += delta;
			idx += (idx & -idx);
		}
	}

	void update_range(int l, int r, int x) {
		update(l, x, bit1);
		update(r + 1, -x, bit1);
		update(l, x * (l - 1), bit2);
		update(r + 1, -x * r, bit2);
	}
};
