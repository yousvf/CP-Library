class DSU {
private:
	vector<int> Set, sz, parity;
	vector<bool> bipartite;

public:
	DSU(int n) : Set(n + 1), sz(n + 1, 1), parity(n + 1, 0), bipartite(n + 1, true) {
		for(int i = 1; i <= n; i++) Set[i] = i;
	}

	pair<int, int> find(int x) {
		if(x != Set[x]) {
			pair<int, int> p = find(Set[x]);
			Set[x] = p.first;
			parity[x] ^= p.second;
		}

		return {Set[x], parity[x]};
	}

	void unite(int u, int v) {
		pair<int, int> pu = find(u);
		int root_u = pu.first;
		int x = pu.second;

		pair<int, int> pv = find(v);
		int root_v = pv.first;
		int y = pv.second;

		if(root_u == root_v) {
			if(x == y) bipartite[root_u] = false;
		}
		else {
			if(sz[root_u] < sz[root_v]) {
				swap(root_u, root_v);
				swap(x, y);
			}

			sz[root_u] += sz[root_v];
			Set[root_v] = root_u;
			parity[root_v] = x ^ y ^ 1;
			bipartite[root_u] = bipartite[root_u] && bipartite[root_v];
		}
	}

	bool is_bipartite(int x) { return bipartite[find(x).first]; }
};
