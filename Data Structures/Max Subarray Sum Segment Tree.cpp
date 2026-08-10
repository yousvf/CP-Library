struct SegmentTree {
#define L 2 * node + 1
#define R 2 * node + 2
#define mid (l + r >> 1)
 
private:
	struct Node {
		int ans, sum, pre, suf;
	};

	int sz, skip = LLONG_MAX;
	vector<Node> seg;

	Node merge(Node& a, Node& b) {
		Node ret;
		ret.ans = max({a.ans, b.ans, a.suf + b.pre});
		ret.pre = max(a.sum + b.pre, a.pre);
		ret.suf = max(b.sum + a.suf, b.suf);
		ret.sum = a.sum + b.sum;
		
		return ret;
	}

	void build(int l, int r, int node, vector<int>& a) {
		if(l == r) {
			if(l < a.size()) seg[node] = {max(0LL, a[l]), a[l], max(0LL, a[l]), max(0LL, a[l])};
			return;
		}

		build(l, mid, L, a);
		build(mid + 1, r, R, a);
		seg[node] = merge(seg[L], seg[R]);
	}

	void update(int l, int r, int node, int idx, int val) {
		if(l == r) {
			seg[node] = {max(0LL, val), val, max(0LL, val), max(0LL, val)};
			return;
		}

		if(idx <= mid) update(l, mid, L, idx, val);
		else update(mid + 1, r, R, idx, val);
		seg[node] = merge(seg[L], seg[R]);
	}
	
public:
	SegmentTree(vector<int>& a) {
		sz = 1;
		int n = a.size();
		while(sz < n) sz *= 2;
		seg = vector<Node> (sz * 2);
		build(0, sz - 1, 0, a);
	}

	void update(int idx, int val) {
		update(0, sz - 1, 0, idx, val);
	}

	int query() {
		return seg[0].ans;
	}
 
#undef L
#undef R
#undef mid
};
