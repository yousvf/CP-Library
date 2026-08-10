struct Edge {
	int u, v;
	int cap, flow = 0;
	Edge(int u, int v, int cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
	const int INF = 1e18;
	vector<Edge> edges;
	vector<vector<int>> adj;
	int n, m = 0;
	int s, t;
	vector<int> level, ptr;
	queue<int> q;

	Dinic(int n, int s, int t) : n(n), s(s), t(t) {
		adj.resize(n + 1);
		level.resize(n + 1);
		ptr.resize(n + 1);
	}

	void add_edge(int u, int v, int cap) {
		edges.emplace_back(u, v, cap);
		edges.emplace_back(v, u, 0);
		adj[u].push_back(m);
		adj[v].push_back(m + 1);
		m += 2;
	}

	bool bfs() {
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int id : adj[u]) {
				if(edges[id].cap == edges[id].flow) continue;
				if(level[edges[id].v] != -1) continue;
				level[edges[id].v] = level[u] + 1;
				q.push(edges[id].v);
			}
		}

		return level[t] != -1;
	}

	int dfs(int u, int pushed) {
		if(pushed == 0) return 0;
		if(u == t) return pushed;

		for(int& cid = ptr[u]; cid < adj[u].size(); cid++) {
			int id = adj[u][cid];
			int v = edges[id].v;
			if(level[u] + 1 != level[v]) continue;
			int tr = dfs(v, min(pushed, edges[id].cap - edges[id].flow));
			if(tr == 0) continue;
			edges[id].flow += tr;
			edges[id ^ 1].flow -= tr;
			return tr;
		}

		return 0;
	}

	int flow() {
		int f = 0;
		while(true) {
			fill(level.begin(), level.end(), -1);
			level[s] = 0;
			q.push(s);
			if(!bfs()) break;
			fill(ptr.begin(), ptr.end(), 0);
			while(int pushed = dfs(s, INF)) f += pushed;
		}

		return f;
	}
};
