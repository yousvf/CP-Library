struct PersistentSegTree {
#define mid (l + r >> 1)

    private:
        int sz, n, skip = 0, nodes = 1;
        vector<int> seg, lc, rc;

        int merge(int a, int b) {
            return a + b;
        }

        int leaf(int val) {
            int node = nodes++;
            seg[node] = val;
            return node;
        }

        int parent(int lft, int rght) {
            int node = nodes++;
            seg[node] = merge(seg[lft], seg[rght]);
            lc[node] = lft;
            rc[node] = rght;
            return node;
        }

        int build(int l, int r) {
            if(l == r) return leaf(0);
            return parent(build(l, mid), build(mid + 1, r));
        }

        void update(int l, int r, int &node, int idx, int val) {
            seg[nodes] = seg[node] + val;
            lc[nodes] = lc[node];
            rc[nodes] = rc[node];
            node = nodes++;
            if(l == r) return;
            if(idx <= mid) update(l, mid, lc[node], idx, val);
            else update(mid + 1, r, rc[node], idx, val);
        }

        int query(int l, int r, int nodeA, int nodeB, int k) {
            if(l == r) return l;
            int cnt = seg[lc[nodeB]] - seg[lc[nodeA]];
            if(cnt >= k) return query(l, mid, lc[nodeA], lc[nodeB], k);
            return query(mid + 1, r, rc[nodeA], rc[nodeB], k - cnt);
        }

    public:
        int build(int x) {
            n = x;
            sz = n * 100;
            seg = lc = rc = vector<int> (sz);
            return build(0, n - 1);
        }

        int query(int k, int nodeA, int nodeB) {
            return query(0, n - 1, nodeA, nodeB, k);
        }

        void update(int idx, int val, int &node) {
            update(0, n - 1, node, idx, val);
        }

#undef mid
};

vector<int> h;
int get(int x) {
    return lower_bound(all(h), x) - h.begin();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for(auto &it : v) {
        cin >> it;
        h.push_back(it);
    }

    sort(all(h));
    vector<int> roots;
    roots.push_back(0);
    PersistentSegTree pst;
    roots[0] = pst.build(n);
    for(int i = 0; i < n; i++) {
        roots.push_back(roots.back());
        pst.update(get(v[i]), 1, roots.back());
    }

    while(q--) {
        int l, r, k;
        cin >> l >> r >> k;
        l--;
        cout << h[pst.query(k, roots[l], roots[r])] << endl;
    }
}
