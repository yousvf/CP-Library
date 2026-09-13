struct FenwickTree {
	int n;
	vector<int> bit;
	FenwickTree(int n) : n(n + 1), bit(n + 1) {}
	int query(int r) {
		int ret = 0;
		while(r > 0) {
			ret += bit[r];
			r -= (r & -r);
		}

		return ret;
	}

	int query(int l, int r) {
		return query(r) - query(l - 1);
	}

	void update(int idx, int delta) {
		while(idx < n) {
			bit[idx] += delta;
			idx += (idx & -idx);
		}
	}
} bit(0);

vector<pair<int, int>> queries[N];
vector<int> adj[N];
int sz[N], ans[N];

void dfs(int u, int par) {
	sz[u] = 1;
	for(int v : adj[u]) {
		if(v == par) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
}

void add(int u, int par, int val) {
	bit.update(u, val);
	for(int v : adj[u]) if(v != par) add(v, u, val);
}

void calc(int u, int par) {
	int big = -1;
	for(int v : adj[u]) {
		if(v == par) continue;
		if(big == -1 || sz[v] > sz[big]) big = v;
	}

	for(int v : adj[u]) {
		if(v != par && v != big) {
			calc(v, u);
			add(v, u, -1);
		}
	}

	if(~big) calc(big, u);
	for(int v : adj[u]) if(v != par && v != big) add(v, u, 1);
	bit.update(u, 1);
	for(auto [d, idx] : queries[u]) ans[idx] = bit.query();
}
