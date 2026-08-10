const int N = 1e2 + 10;

struct Matrix {
	int n;
	int a[N][N] = {};
	Matrix(int n) : n(n) { for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) a[i][j] = 0; }
	Matrix operator *(const Matrix& other) {
		Matrix product(n);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				for(int k = 0; k < n; k++) {
					product.a[i][k] += a[i][j] * other.a[j][k] % MOD;
					if(product.a[i][k] >= MOD) product.a[i][k] -= MOD;
				}
			}
		}

		return product;
	}
};

Matrix exp(Matrix tr, int b) {
	Matrix ret(tr.n);
	for(int i = 0; i < tr.n; i++) ret.a[i][i] = 1;
	while(b) {
		if(b & 1) ret = ret * tr;
		tr = tr * tr;
		b /= 2;
	}

	return ret;
}
