class DSU {
private:
	vector<int> Set, sz;

public:
	DSU(int n) : Set(n + 1), sz(n + 1, 1) {
		for(int i = 1; i <= n; i++) Set[i] = i;
	}

	int find(int x) { return Set[x] == x ? x : (Set[x] = find(Set[x])); }

	void unite(int u, int v) {
		u = find(u);
		v = find(v);
		if(u == v) return;

		if(sz[u] < sz[v]) swap(u, v);
		sz[u] += sz[v];
		Set[v] = u;
	}

	bool connected(int x, int y) { return find(x) == find(y); }
};
