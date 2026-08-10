uint32_t gospers_hack(const uint32_t& n) {
	const uint32_t c = n & -n;
	const uint32_t r = n + c;
	return (((r ^ n) >> 2LL) / c) | r;
}
