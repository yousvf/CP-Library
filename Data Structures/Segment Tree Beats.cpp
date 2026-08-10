mid);
	chmin(ql, qr, val, R, mid + 1, r);
	seg[node] = merge(seg[L], seg[R]);
}

void chmax(int ql, int qr, int val, int node = 0, int l = 0, int r = n - 1) {
	if(qr < l || r < ql || val <= seg[node].min1) return;
	if(ql <= l && r <= qr && val < seg[node].min2) {
		push_min(node, val, l == r);
		return;
	}

	push_down(node, l, r);

	chmax(ql, qr, val, L, l, mid);
	chmax(ql, qr, val, R, mid + 1, r);
	seg[node] = merge(seg[L], seg[R]);
}

int query_sum(int ql, int qr, int node = 0, int l = 0, int r = n - 1) {
	if(qr < l || r < ql) return 0;
	if(ql <= l && r <= qr) return seg[node].sum;
	push_down(node, l, r);
		
	return query_sum(ql, qr, L, l, mid) + query_sum(ql, qr, R, mid + 1, r);
}

#undef L
#undef R
#undef mid
