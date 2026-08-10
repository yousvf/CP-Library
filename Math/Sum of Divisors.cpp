const int MOD2 = 500000004;
int sum(int x, int y) {
	return (((y - x + 1) % MOD) * ((x + y) % MOD) % MOD) * MOD2 % MOD;
}

int sum_of_divisors(int n) {
	int i = 1, res = 0;

	while(i <= n) {
		int divisor = n / i;
		int lst = n / divisor;
		res = (res + divisor * sum(i, lst)) % MOD;
		i = lst + 1;
	}

	return res;
}
