for(int i = 0; i < LOG; i++) {
	for(int j = 0; j < (1 << LOG); j++) {
		if((j >> i) & 1) dp[j] += dp[j ^ (1 << i)];
	}
}
