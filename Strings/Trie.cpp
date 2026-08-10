struct Trie {
	struct Node {
		Node *child[26];
		int Pre, End;
		Node() {
			memset(child, 0, sizeof(child));
			Pre = End = 0;
		}
	};

	Node *root = new Node();

	void insert(string &s) {
		Node *cur = root;
		for(auto it : s) {
			int x = it - 'a';
			if(cur -> child[x] == 0) {
				cur -> child[x] = new Node();
			}

			cur = cur -> child[x];
			cur -> Pre++;
		}

		cur -> End++;
	}

	int count(string &s) {
		Node *cur = root;
		for(auto it : s) {
			int x = it - 'a';
			if(cur -> child[x] == 0) return 0;
			cur = cur -> child[x];
		}

		return cur -> Pre;
	}
};
