struct Query {
	int l, r, idx;
	bool operator<(const Query &sc) const {
		return make_pair(l / SQ, r) < make_pair(sc.l / SQ, sc.r);
	}
};

vector<int> ans;
vector<Query> queries;
int res;

void add(int i) {}

void remove(int i) {}

void Mo_Algorithm() {
	sort(all(queries));

	int l = 1, r = 0;
	for(Query q : queries) {
		while(r < q.r) add(v[++r]);
		while(r > q.r) remove(v[r--]);
		while(l < q.l) remove(v[l++]);
		while(l > q.l) add(v[--l]);

		ans[q.idx] = res;
	}
}
