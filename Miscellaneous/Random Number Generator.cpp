mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
int rnd(int lim) {
	uniform_int_distribution<int> uid(1, lim);
	return uid(rng);
}
