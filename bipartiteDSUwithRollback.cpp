class DSU {
private:
	int comps;
	int bp = true;
	vector<int> Set, sz, parity, bipartite;
	vector<pair<int &, int>> history;
	
public:
	DSU() {}
	DSU(int n) : Set(n + 1), sz(n + 1, 1), parity(n + 1, 0), bipartite(n + 1, 1), comps(n) { 
		for(int i = 1; i <= n; i++) Set[i] = i;
	}
	
	pair<int, int> get(int u) {
		int p = 0;
		while(u != Set[u]) {
			p ^= parity[u];
			u = Set[u];
		}

		return {u, p};
	}
	
	int get_ans() { return comps; }
	
	void unite(int u, int v) {
		pair<int, int> pa = get(u);
		int root_u = pa.first;
		int x = pa.second;

		pair<int, int> pb = get(v);
		int root_v = pb.first;
		int y = pb.second;

		if(root_u == root_v) {
			if(x == y) {
				history.push_back({bp, bp});
				history.push_back({bipartite[root_u], bipartite[root_u]});
				bipartite[root_u] = bp = 0;
			}

			return;
		}
		if(sz[root_u] < sz[root_v]) {
			swap(root_u, root_v);
			swap(x, y);
		}
		
		history.push_back({Set[root_v], Set[root_v]});
		history.push_back({sz[root_u], sz[root_u]});
		history.push_back({parity[root_v], parity[root_v]});
		history.push_back({bipartite[root_u], bipartite[root_u]});
		history.push_back({comps, comps});
		history.push_back({bp, bp});
		
		Set[root_v] = root_u;
		sz[root_u] += sz[root_v];
		parity[root_v] = x ^ y ^ 1;
		bipartite[root_u] &= bipartite[root_v];
		if(!bipartite[root_u]) bp = false;
		comps--;
	}
	
	bool isBipartite(int u) { return bipartite[get(u).first]; }
	bool isBipartite() { return bp; }
	int snapshot() { return history.size(); }
	
	void rollback(int until) {
		while(snapshot() > until) {
			history.back().first = history.back().second;
			history.pop_back();
		}
	}
};
