// Tarjan's Algorithm (all variations)

vector<vector<int>> components;
vector<pair<int, int>> bridges;
set<int> art_points;
int low[N], disc[N];
vector<int> adj[N];
bool instack[N];
stack<int> stck;
int timer;
bool root;


// Tarjan's for finding Strongly Connected Components

void tarjan(int node) {
	low[node] = disc[node] = ++timer, instack[node] = 1;
	stck.push(node);

	for(int child : adj[node]) {
		if(!disc[child]) {
			tarjan(child);
			low[node] = min(low[node], low[child]);
		}
		else if(instack[child]) {
			low[node] = min(low[node], disc[child]);
		}
	}

	if(low[node] == disc[node]) {
		components.push_back(vector<int> ());
		int x = -1;

		while(x != node) {
			x = stck.top();
			stck.pop();
			instack[x] = 0;
			components.back().push_back(x);
		}
	}
}


// Tarjan's for finding Bridges

void tarjan(int node, int parent) {
	low[node] = disc[node] = ++timer;

	for(int child : adj[node]) {
		if(child == parent) continue;

		if(!disc[child]) {
			tarjan(child, node);
			low[node] = min(low[node], low[child]);
			if(low[child] == disc[child]) bridges.push_back({node, child});
		}
		else low[node] = min(low[node], disc[child]);
	}
}


// Tarjan's for finding Articulation Points

void tarjan(int node, int parent = -1) {
	low[node] = disc[node] = ++timer;

	for(int child : adj[node]) {
		if(child == parent) continue;

		if(!disc[child]) {
			tarjan(child, node);
			low[node] = min(low[node], low[child]);
			if(low[child] >= disc[node]) {
				if(disc[node] == 1 && !root) root = 1;
				else art_points.insert(node);
			}
		}
		else low[node] = min(low[node], disc[child]);
	}
}
