class DSU {
private:
	int comps;
	vector<int> Set, sz;
	vector<pair<int &, int>> history;
	
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
		
		history.push_back({Set[v], Set[v]});
		history.push_back({sz[u], sz[u]});
		history.push_back({comps, comps});
		
		Set[v] = u;
		sz[u] += sz[v];
		comps--;
	}
	
	int snapshot() { return history.size(); }
	
	void rollback(int until) {
		while(snapshot() > until) {
			history.back().first = history.back().second;
			history.pop_back();
		}
	}
} dsu;

struct Query { int t, u, v; };
vector<Query> seg[N * 4];

void update(Query q, int l, int r, int node, int lq, int rq) {
	if(l > rq || r < lq) return;
	if(l >= lq && r <= rq) {
		seg[node].push_back(q);
		return;
	}
	
	int mid = l + r >> 1;
	update(q, l, mid, 2 * node + 1, lq, rq);
	update(q, mid + 1, r, 2 * node + 2, lq, rq);
}

int ans[N];
void dfs(int l, int r, int node) {
	int snap = dsu.snapshot();
	
	for(Query &q : seg[node]) {
		if(q.t == 1) dsu.unite(q.u, q.v);
	}
	
	if(l == r) {
		for(Query &q : seg[node]) {
			if(q.t == 2) ans[l] = dsu.get_ans();
		}
	}
	else {
		int mid = l + r >> 1;
		dfs(l, mid, 2 * node + 1);
		dfs(mid + 1, r, 2 * node + 2);
	}
	
	dsu.rollback(snap);
}
