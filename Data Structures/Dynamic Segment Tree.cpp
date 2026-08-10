class DynSegTree {
#define mid (l + r >> 1)

private:
	struct Node {
		int val = 0;
		Node *l = nullptr;
		Node *r = nullptr;
	};

	Node *root = new Node;
	const int n, skip = 0;

	int merge(int a, int b) {
		return a + b;
	}

	void update(int idx, int x, Node* &cur, int l, int r) {
		if(cur == nullptr) cur = new Node;
		if(l == r) {
			cur -> val += x;
			return;
		}

		if(idx <= mid) update(idx, x, cur -> l, l, mid);
		else update(idx, x, cur -> r, mid + 1, r);

		cur -> val = merge(
						(cur -> l ? cur -> l -> val : skip),
						(cur -> r ? cur -> r -> val : skip)
					);
	}

	int query(int ql, int qr, Node *cur, int l, int r) {
		if(l > qr || r < ql || cur == nullptr) return skip;
		if(l >= ql && r <= qr) return cur -> val;

		return merge(query(ql, qr, cur -> l, l, mid), query(ql, qr, cur -> r, mid + 1, r));
	}
	
public:
	DynSegTree(int n) : n(n) {}
	void update(int idx, int x) { update(idx, x, root, 0, n); }
	int query(int ql, int qr) { return query(ql, qr, root, 0, n); }

#undef mid
};
