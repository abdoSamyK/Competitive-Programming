struct BIT { // 1-based
  int n;
  vector<ll> bt;
  int lg;
  BIT(int sz) {
    n = sz;
    bt.assign(sz + 1, 0);
    lg = 1;
    while ((lg << 1) <= n) lg <<= 1;
  }

  int lowbit(int x) {
    return x & -x;
  }

  void add(int idx, ll val) {
    if (idx <= 0) return;
    while (idx <= n) {
      bt[idx] += val;
      idx += lowbit(idx);
    }
  }

  ll get(int idx) {
    ll ans = 0;
    while (idx > 0) {
      ans += bt[idx];
      idx -= lowbit(idx);
    }
    return ans;
  }
  ll get_idx(int idx) {
    return get(idx) - get(idx - 1);
  }
  ll get_range(int l, int r) {
    return get(r) - get(l - 1);
  }

  void set(int idx, ll val) {
    ll old = get_range(idx, idx);
    add(idx, val - old);
  }
  ll lower_bound(ll x) {
    ll sum = 0;
    int idx = 0;

    for (int pw = lg; pw > 0; pw >>= 1) {
      int nxt = idx + pw;
      if (nxt <= n && sum + bt[nxt] < x) { // for upper bound (sum + bt[nxt] <= x)
        sum += bt[nxt];
        idx = nxt;
      }
    }
    return idx + 1;
  }
};