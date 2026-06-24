struct SegmentTree {
#define L 2 * node + 1
#define R 2 * node + 2
#define mid (l + r >> 1)

private:
	int n, sz, skip = LLONG_MAX;
	vector<int> seg;

	int merge(int a, int b) {
		return min(a, b);
	}

	void build(int l, int r, int node, vector<int>& a) {
		if(l == r) {
			if(l < a.size()) seg[node] = a[l];
			return;
		}

		build(l, mid, L, a);
		build(mid + 1, r, R, a);
		seg[node] = merge(seg[L], seg[R]);
	}

	void update(int l, int r, int node, int idx, int val) {
		if(l == r) {
			seg[node] = val;
			return;
		}

		if(idx <= mid) update(l, mid, L, idx, val);
		else update(mid + 1, r, R, idx, val);
		seg[node] = merge(seg[L], seg[R]);
	}

	int query(int l, int r, int node, int lq, int rq) {
		if(r < lq || l > rq) return skip;
		if(l >= lq && r <= rq) return seg[node];

		int lft = query(l, mid, L, lq, rq);
		int rght = query(mid + 1, r, R, lq, rq);
		return merge(lft, rght);
	}
	
public:
	SegmentTree(vector<int>& a) {
		sz = 1;
		n = a.size();
		while(sz < n) sz *= 2;
		seg = vector<int> (sz * 2, skip);
		build(0, sz - 1, 0, a);
	}

	void update(int idx, int val) {
		update(0, sz - 1, 0, idx, val);
	}

	int query(int l, int r) {
		return query(0, sz - 1, 0, l, r);
	}

#undef L
#undef R
#undef mid
};
