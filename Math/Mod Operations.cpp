int add(int a, int b) {
	return ((a % MOD) + (b % MOD)) % MOD;
}

int mul(int a, int b) {
	return ((a % MOD) * (b % MOD)) % MOD;
}

int sub(int a, int b) {
	return ((a % MOD) - (b % MOD) + MOD) % MOD;
}

int neg(int a) {
	return (a % MOD + MOD) % MOD;
}

int exp(int a, int b) {
	if(b <= 0) return 1;
	int ret = exp(a * a % MOD, b / 2);
	if(b % 2) ret = ret * a % MOD;
	return ret;
}

int inv(int a) { 
	return exp(a, MOD - 2);
}

int Div(int a, int b) {
	return ((a % MOD) * (inv(b % MOD))) % MOD;
}

int fac(int n) {
	if(n == 0) return 1;
	return mul(n, fac(n - 1));
}
