// Mo's with Updates --> O(qn^(2/3))
// Optimal size for SQ is (2 * n^2)^(1/3). Also 2500 probably works fine
// Use sqrt decomposition if it asks for MEX in a range, update takes o(1)

struct Query {
	int l, r, t, idx;
	bool operator<(const Query &sc) const {
		if(l / SQ == sc.l / SQ) {
			if(r / SQ == sc.r / SQ) return t < sc.t;
			return r / SQ < sc.r / SQ;
		}

		return l / SQ < sc.l / SQ;
	}
};

struct Update {
	int pos, old, cur;
};

int freq[N];
int rvmp[N], ans[N];
vector<int> v;
vector<Query> queries;
vector<Update> updates;
int res;

void add(int i) {
	freq[i]++;
	if(freq[i] == 1) res += rvmp[i];
}

void remove(int i) {
	freq[i]--;
	if(freq[i] == 0) res -= rvmp[i];
}

void update(int i, int x, int l, int r) {
	if(l <= i && r >= i) {
		add(x);
		remove(v[i]);
	}

	v[i] = x;
}

void Mo_Algorithm() {
	sort(all(queries));

	int l = 0, r = -1, t = updates.size();
	for(Query q : queries) {
		while(t < q.t) update(updates[t].pos, updates[t].cur, l, r), t++;
		while(t > q.t) t--, update(updates[t].pos, updates[t].old, l, r);
		while(l > q.l) add(v[--l]);
		while(l < q.l) remove(v[l++]);
		while(r > q.r) remove(v[r--]);
		while(r < q.r) add(v[++r]);

		ans[q.idx] = res;
	}
}
