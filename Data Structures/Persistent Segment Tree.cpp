struct PersistentSegTree {
#define mid (l + r >> 1)

	private:
		int sz, n, skip = 0, nodes = 1;
		vector<int> seg, lc, rc;

		int merge(int a, int b) {
			return a + b;
		}

		int leaf(int val) {
			int node = nodes++;
			seg[node] = val;
			return node;
		}

		int parent(int lft, int rght) {
			int node = nodes++;
			seg[node] = merge(seg[lft], seg[rght]);
			lc[node] = lft;
			rc[node] = rght;
			return node;
		}

		int build(int l, int r, vector<int>& a) {
			if(l == r) return l < a.size() ? leaf(a[l]) : leaf(skip);
			return parent(build(l, mid, a), build(mid + 1, r, a));
		}

		void update(int l, int r, int &node, int idx, int val) {
			seg[nodes] = seg[node] + val;
			lc[nodes] = lc[node];
			rc[nodes] = rc[node];
			node = nodes++;
			if(l == r) return;
			if(idx <= mid) update(l, mid, lc[node], idx, val);
			else update(mid + 1, r, rc[node], idx, val);
		}

		int query(int l, int r, int node, int ql, int qr) {
			if(l > qr || r < ql) return skip;
			if(l >= ql && r <= qr) return seg[node];
			int lft = query(l, mid, lc[node], ql, qr);
			int rght = query(mid + 1, r, rc[node], ql, qr);
			return merge(lft, rght);
		}

	public:
		int build(vector<int>& a) {
			n = a.size();
			sz = n * 30;
			seg = lc = rc = vector<int> (sz);
			return build(0, n - 1, a);
		}

		int query(int l, int r, int node) {
			return query(0, n - 1, node, l, r);
		}

		void update(int idx, int val, int &node) {
			update(0, n - 1, node, idx, val);
		}

#undef mid
};
