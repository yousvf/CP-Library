int anc[N][LOG], depth[N];
vector<int> adj[N];

void BuildAncestors(int node, int par) {
	anc[node][0] = par;
	depth[node] = depth[par] + 1;
		
	for(int i = 1; i < LOG; i++) {
		int p = anc[node][i - 1];
		anc[node][i] = anc[p][i - 1];
	}

	for(auto v : adj[node]) {
		if(par != v)
			BuildAncestors(v, node);
	}
}

int KthAncestor(int node, int k) {
	for(int i = 0; i < LOG; i++) {
		if((k >> i) & 1) node = anc[node][i];
	}

	return node;
}

int LCA(int u, int v) {
	if(depth[u] < depth[v]) swap(u, v);
	u = KthAncestor(u, depth[u] - depth[v]);
	if(u == v) return u;

	for(int i = LOG - 1; i >= 0; i--) {
		if(anc[u][i] != anc[v][i]) {
			u = anc[u][i];
			v = anc[v][i];
		}
	}

	return anc[u][0];
}

int dis(int u, int v) {
	int lca = LCA(u, v);
	return depth[u] + depth[v] - 2 * depth[lca];
}
