struct BIT { // 1-based
  int n;
  vector<ll> bt;

  BIT(int sz) {
    n = sz;
    bt.assign(n + 1, 0);
  }

  int lowbit(int x) {
    return x & -x;
  }

  void add(int idx, ll val) {
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
};