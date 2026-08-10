struct MergeSortTree {
#define L 2 * node + 1
#define R 2 * node + 2
#define mid (l + r >> 1)

	private:
		int n, sz, skip = 0;
		vector<vector<int>> seg;

		void merge(int node) {
			int i = 0, j = 0;
			while(i < seg[L].size() && j < seg[R].size()) {
				if(seg[L][i] < seg[R][j]) seg[node].push_back(seg[L][i++]);
				else seg[node].push_back(seg[R][j++]);
			}

			while(i < seg[L].size()) seg[node].push_back(seg[L][i++]);
			while(j < seg[R].size()) seg[node].push_back(seg[R][j++]);
		}

		void build(int l, int r, int node, vector<int>& a) {
			if(l == r) {
				if(l < a.size()) seg[node].push_back(a[l]);
				return;
			}

			build(l, mid, L, a);
			build(mid + 1, r, R, a);
			merge(node);
		}

		int query(int l, int r, int node, int ql, int qr, int x) {
			if(r < ql || l > qr) return skip;
			if(r <= qr && l >= ql) {
				int low = 0, high = seg[node].size() - 1, ret = seg[node].size();
				while(low <= high) {
					int Mid = low + (high - low) / 2;
					if(seg[node][Mid] > x) {
						ret = Mid;
						high = Mid - 1;
					}
					else low = Mid + 1;
				}

				return seg[node].size() - ret;
			}

			int lft = query(l, mid, L, ql, qr, x);
			int rght = query(mid + 1, r, R, ql, qr, x);
			return lft + rght;
		}

	public:
		MergeSortTree(vector<int>& a) {
			sz = 1;
			n = a.size();
			while(sz < n) sz *= 2;
			seg = vector<vector<int>> (sz * 2);
			build(0, sz - 1, 0, a);
		}

		int query(int l, int r, int x) {
			return query(0, sz - 1, 0, l, r, x);
		}

#undef L
#undef R
#undef mid
};
