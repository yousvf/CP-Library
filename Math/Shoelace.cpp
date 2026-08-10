struct point { int x, y; };

int area(const vector<point>& fig) {
	int res = 0;
	for(int i = 0; i < fig.size(); i++) {
		point p = i ? fig[i - 1] : fig.back();
		point q = fig[i];
		res += (p.x - q.x) * (p.y + q.y);
	}

	return abs(res) / 2;
}
