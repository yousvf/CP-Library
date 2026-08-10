struct BinaryTrie {
	struct Node {
		Node *child[2];
		int freq[2];
		Node() {
			child[0] = child[1] = 0;
			freq[0] = freq[1] = 0;
		}
	};

	Node *root = new Node();

	void insert(int n) {
		Node *cur = root;
		for(int i = 29; i >= 0; i--) {
			int bit = (n >> i) & 1;
			if(cur -> child[bit] == 0) cur -> child[bit] = new Node();
			cur -> freq[bit]++;
			cur = cur -> child[bit];
		}
	}

	void del(int n, int i, Node *cur) {
		if(!cur || i == -1) return;
		int bit = (n >> i) & 1;
		del(n, i - 1, cur -> child[bit]);
		cur -> freq[bit]--;
		if(cur -> freq[bit] == 0) {
			delete cur -> child[bit];
			cur -> child[bit] = 0;
		}
	}
};
