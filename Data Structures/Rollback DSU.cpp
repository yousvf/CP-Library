class DSU {
private:
	int comps;
	vector<int> Set, sz;
	vector<array<int, 5>> history;
	
public:
	DSU() {}
	DSU(int n) : Set(n + 1), sz(n + 1, 1), comps(n) { 
		for(int i = 1; i <= n; i++) Set[i] = i;
	}
	
	int get(int u) { return (Set[u] == u) ? u : get(Set[u]); }
	int get_ans() { return comps; }
	
	void unite(int u, int v) {
		u = get(u);
		v = get(v);
		if(u == v) return;
		if(sz[u] < sz[v]) swap(u, v);
		
		history.push_back({u, sz[u], v, Set[v], comps});
		
		Set[v] = u;
		sz[u] += sz[v];
		comps--;
	}

	void rollback() {
		auto [u, szu, v, setv, comp] = history.back();
		sz[u] = szu;
		Set[v] = setv;
		comps = comp;
		history.pop_back();
	}
};
