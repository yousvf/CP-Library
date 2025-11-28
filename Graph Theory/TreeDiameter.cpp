pair<int, int> farthest(int s, vector<int>& dis) {
	dis[s] = 0;
	queue<int> q;
	q.push(s);

	int ret;
	int mx = -INF;
	while(!q.empty()) {
		int u = q.front();
		q.pop();

		for(int v : adj[u]) {
			if(dis[v] == INF) {
				q.push(v);
				dis[v] = dis[u] + 1;
			}
		}

		ret = u;
		mx = max(mx, dis[u]);
	}

	return {ret, mx};
}