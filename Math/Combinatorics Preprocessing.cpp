vector<int> fac, inv, finv;
void init(int n) {
	fac.resize(n + 1);
	inv.resize(n + 1);
	finv.resize(n + 1);
	fac[0] = inv[0] = inv[1] = finv[0] = finv[1] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
	for(int i = 2; i <= n; i++) inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;
	for(int i = 2; i <= n; i++) finv[i] = finv[i - 1] * inv[i] % MOD;
}
