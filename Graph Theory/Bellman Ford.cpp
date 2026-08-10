vector<tuple<int, int, int>> edges;
int dis[N];

dis[1] = 0;
for(int i = 0; i < n - 1; i++) {
	for(auto edge : edges) {
		int u = get<0> (edge), v = get<1> (edge), len = get<2> (edge);
		if(dis[u] != INF) 
			dis[v] = min(dis[v], dis[u] + len);
	}
}
