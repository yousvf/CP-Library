int dis[N][N];

for(int i = 1; i <= n; i++) {
	for(int j = 1; j <= n; j++) {
		for(int k = 1; k <= n; k++) {
			// if(dis[j][i] < INF && dis[i][k] < INF)
				dis[j][k] = min(dis[j][k], dis[j][i] + dis[i][k]);
		}
	}
}
