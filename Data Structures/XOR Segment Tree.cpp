struct XORSegmentTree {
#define L 2 * node + 1
#define R 2 * node + 2
#define mid (l + r >> 1)

private:
	int n, sz, depth = 0, skip = 0;
	vector<int> seg;

	int merge(int a, int b) {
		return a ^ b;
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
			seg[node] ^= val;
			return;
		}

		if(idx <= mid) update(l, mid, L, idx, val);
		else update(mid + 1, r, R, idx, val);
		seg[node] = merge(seg[L], seg[R]);
	}

	int query(int l, int r, int node, int lq, int rq, int x, int dep) {
		if(r < lq || l > rq) return skip;
		if((x >> dep) & 1LL) {
			int len = r - l + 1;
			if(node & 1LL) return query(l + len, r + len, node + 1, lq + len, rq + len, x ^ (1LL << dep), dep);
			return query(l - len, r - len, node - 1, lq - len, rq - len, x ^ (1LL << dep), dep);
		}
		
		if(l >= lq && r <= rq) return seg[node];
		int lft = query(l, mid, L, lq, rq, x, dep - 1);
		int rght = query(mid + 1, r, R, lq, rq, x, dep - 1);
		return merge(lft, rght);
	}
	
public:
	XORSegmentTree(vector<int>& a) {
		sz = 1;
		n = a.size();
		while(sz < n) sz *= 2, depth++;
		seg = vector<int> (sz * 2, skip);
		build(0, sz - 1, 0, a);
	}

	void update(int idx, int val) {
		update(0, sz - 1, 0, idx, val);
	}

	int query(int l, int r, int x) {
		if(x >> depth) return 0;
		return query(0, sz - 1, 0, l, r, x, depth);
	}

#undef L
#undef R
#undef mid
};
