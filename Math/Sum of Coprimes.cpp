int sum_of_coprimes(int n) {
	return n != 1 ? phi(n) * n / 2 : 1;
}
