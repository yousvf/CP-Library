const int N = 5e5 + 10, MOD = 998244353, INF = 3e15, LOG = 23, SQ = 320; // SQ = 317 for 1e5, 448 for 2e5

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
	int val, prior, sz, sum;
	int B, C;
	bool rev;
	Node *l, *r;
	Node(int x) : val(x), sum(x), prior(rng()), sz(1), B(1), C(0), rev(false), l(nullptr), r(nullptr) {}
} *root;

int size(Node *treap) { return treap ? treap -> sz : 0LL; }
int s(Node *treap) { return treap ? treap -> sum : 0LL; }

void pull(Node *treap) {
	if(!treap) return;
	treap -> sum = (treap -> val + s(treap -> l) + s(treap -> r)) % MOD;
	treap -> sz = 1 + size(treap -> l) + size(treap -> r);
}

void push(Node *treap) {
	if(!treap) return;

	if(treap -> rev) {
		treap -> rev = false;
		swap(treap -> l, treap -> r);
		if(treap -> l) treap -> l -> rev ^= 1;
		if(treap -> r) treap -> r -> rev ^= 1;
	}

	if(treap -> l) {
		treap -> l -> B = treap -> B * treap -> l -> B % MOD;
		treap -> l -> C = (treap -> C + treap -> B * treap -> l -> C) % MOD;
		treap -> l -> sum = (treap -> B * treap -> l -> sum % MOD + treap -> C * size(treap -> l) % MOD) % MOD;
	}
		
	if(treap -> r) {
		treap -> r -> B = treap -> B * treap -> r -> B % MOD;
		treap -> r -> C = (treap -> C + treap -> B * treap -> r -> C) % MOD;
		treap -> r -> sum = (treap -> B * treap -> r -> sum % MOD + treap -> C * size(treap -> r) % MOD) % MOD;
	}

	treap -> val = (treap -> val * treap -> B + treap -> C) % MOD;
	treap -> B = 1;
	treap -> C = 0;

	pull(treap);
}

void split(Node *treap, Node *&l, Node *&r, int val) {
	if(!treap) {
		l = r = nullptr;
		return;
	}
		
	push(treap);
		
	if(size(treap -> l) + 1 <= val) {
		split(treap -> r, treap -> r, r, val - (size(treap -> l) + 1));
		l = treap;
	}
	else {
		split(treap -> l, l, treap -> l, val);
		r = treap;
	}

	pull(treap);
}

void merge(Node *&treap, Node *l, Node *r) {
	push(l), push(r);
		
	if(!l || !r) {
		treap = l ? l : r;
		return;
	}
		
	if(l -> prior < r -> prior) {
		merge(l -> r, l -> r, r);
		treap = l;
	}
	else {
		merge(r -> l, l, r -> l);
		treap = r;
	}

	pull(treap);
}

void reverse(Node *&treap, int l, int r) {
	Node *a, *b, *c;
	split(treap, a, b, l - 1);
	split(b, b, c, r - l + 1);
	b -> rev = true;
	merge(treap, a, b);
	merge(treap, treap, c); 
}

void insert(Node *&treap, int i, int x) {
	Node *y = new Node(x);
	Node *a, *b;
	split(treap, a, b, i);
	merge(treap, a, y);
	merge(treap, treap, b);
}

void remove(Node *&treap, int i) {
	Node *a, *b, *c;
	split(treap, a, b, i);
	split(b, b, c, 1);
	merge(treap, a, c);
}

void affine(Node *&treap, int l, int r, int b, int c) {
	Node *x, *y, *z;
	split(treap, x, y, l - 1);
	split(y, y, z, r - l + 1);
	y -> B = b * y -> B % MOD;
	y -> C = (c + b * y -> C) % MOD;
	y -> sum = (b * y -> sum % MOD + c * size(y) % MOD) % MOD;
	merge(treap, x, y);
	merge(treap, treap, z);
}

int get_sum(Node *&treap, int l, int r) {
	Node *a, *b, *c;
	split(treap, a, b, l - 1);
	split(b, b, c, r - l + 1);
	push(b);
	int ret = b -> sum;
	merge(treap, a, b);
	merge(treap, treap, c);
	return ret;
}

ostream &operator<<(ostream &os, Node *n) {
	if(!n) return os;
	os << n -> l;
	os << n -> val << ' ';
	os << n -> r;
	return os;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q;
	cin >> n >> q;
	for(int i = 0; i < n; i++) {
		int x;
		cin >> x;
		merge(root, root, new Node(x));
	}

	while(q--) {
		int op;
		cin >> op;
		if(op == 0) {
			int i, x;
			cin >> i >> x;
			insert(root, i, x);
		}
		else if(op == 1) {
			int i;
			cin >> i;
			remove(root, i);
		}
		else if(op == 2) {
			int l, r;
			cin >> l >> r;
			l++, r++;
			reverse(root, l, r - 1);
		}
		else if(op == 3) {
			int l, r, b, c;
			cin >> l >> r >> b >> c;
			l++, r++;
			affine(root, l, r - 1, b, c);
		}
		else {
			int l, r;
			cin >> l >> r;
			l++, r++;
			cout << get_sum(root, l, r - 1) << endl;
		}
	}
}
