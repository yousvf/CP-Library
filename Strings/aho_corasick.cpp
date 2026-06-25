const int N = 5e5 + 10, K = 26;

int tr[N][K], fail[N], l[N], nodes = 1;
vector<int> leaf[N];

int id(char c) { return c - 'a'; }

void add_string(string& s, int idx) {
    int node = 1;
    for(auto c : s) {
        if(!tr[node][id(c)]) tr[node][id(c)] = ++nodes;
        node = tr[node][id(c)];
    }

    leaf[node].push_back(idx);
}

vector<int> adj[N];
void build() {
    queue<int> q;
    fail[1] = 1;
    for(int i = 0; i < K; i++) {
        if(tr[1][i]) {
            fail[tr[1][i]] = 1;
            q.push(tr[1][i]);
        }
        else tr[1][i] = 1;
    }

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int i = 0; i < K; i++) {
            if(tr[node][i]) {
                fail[tr[node][i]] = tr[fail[node]][i];
                q.push(tr[node][i]);
            }
            else tr[node][i] = tr[fail[node]][i];
        }

		if(!leaf[fail[node]].empty()) l[node] = fail[node];
		else l[node] = l[fail[node]];
    }

	for(int i = 2; i <= nodes; i++) adj[fail[i]].push_back(i);
}

int dp[N];
void search(string& s) {
    int node = 1;
	for(int i = 0; i < s.length(); i++) {
		node = tr[node][id(s[i])];
		dp[node]++;
	}
}

int ans[N];
void dfs(int u = 1) {
	for(int v : adj[u]) {
		dfs(v);
		dp[u] += dp[v];
	}

	for(int x : leaf[u]) ans[x] = dp[u];
}
