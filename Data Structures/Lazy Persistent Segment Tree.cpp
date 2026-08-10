struct PersistentSegTree {
#define mid (l + r >> 1)

	private:
		int sz, n, skip = 0, nodes = 1;
		vector<int> seg, lc, rc, lazy;

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

		int lazykid(int node, int delta, int l, int r) {
			int Node = nodes++;
			lc[Node] = lc[node];
			rc[Node] = rc[node];
			lazy[Node] = lazy[node];
			lazy[Node] += delta;
			seg[Node] = seg[node] + (r - l + 1) * delta;
			return Node;
		}

		void propagate(int l, int r, int node) {
			if(!lazy[node]) return;

			if(l != r) {
				lc[node] = lazykid(lc[node], lazy[node], l, mid);
				rc[node] = lazykid(rc[node], lazy[node], mid + 1, r);
			}

			lazy[node] = 0;
		}

		int build(int l, int r, vector<int>& a) {
			if(l == r) return l < a.size() ? leaf(a[l]) : leaf(skip);
			return parent(build(l, mid, a), build(mid + 1, r, a));
		}

		int update(int l, int r, int node, int ql, int qr, int val) {
			if(l > qr || r < ql) return node;
			if(l >= ql && r <= qr) return lazykid(node, val, l, r);
			propagate(l, r, node);
			int lft = update(l, mid, lc[node], ql, qr, val);
			int rght = update(mid + 1, r, rc[node], ql, qr, val);
			return parent(lft, rght);
		}

		int query(int l, int r, int node, int ql, int qr) {
			if(l > qr || r < ql) return skip;
			if(l >= ql && r <= qr) return seg[node];
			propagate(l, r, node);
			int lft = query(l, mid, lc[node], ql, qr);
			int rght = query(mid + 1, r, rc[node], ql, qr);
			return merge(lft, rght);
		}

	public:
		int build(vector<int>& a) {
			n = a.size();
			sz = n * 30;
			seg = lc = rc = lazy = vector<int> (sz);
			return build(0, n - 1, a);
		}

		int query(int l, int r, int node) {
			return query(0, n - 1, node, l, r);
		}

		int update(int l, int r, int val, int &node) {
			return update(0, n - 1, node, l, r, val);
		}

#undef mid
};
