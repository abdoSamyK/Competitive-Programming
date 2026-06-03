struct BIT { // 1-based
  int n;
  vector<ll> bt;
  int mxPow; // max pow of two to use it at lower bound...
  BIT(int sz) {
    n = sz;
    bt.assign(sz + 1, 0);
    mxPow = 1;
    while ((mxPow << 1) <= n) mxPow <<= 1;
  }

  int lowbit(int x) { // LSB
    return x & -x;
  }

  void add_idx(int idx, ll val) {
    if (idx <= 0) return;
    while (idx <= n) {
      bt[idx] += val;
      idx += lowbit(idx);
    }
  }

  void set_idx(int idx, ll val) {
    ll old = get_range(idx, idx);
    add_idx(idx, val - old);
  }

  ll get_pref(int idx) {
    ll ans = 0;
    while (idx > 0) {
      ans += bt[idx];
      idx -= lowbit(idx);
    }
    return ans;
  }
  ll get_idx(int idx) {
    return get_pref(idx) - get_pref(idx - 1);
  }
  ll get_range(int l, int r) {
    return get_pref(r) - get_pref(l - 1);
  }

  int lower_bound(ll x) { // finds the smallest index i such that pref[i] >= x,
    ll sum = 0;
    int idx = 0;

    for (int pw = mxPow; pw > 0; pw >>= 1) {
      int nxt = idx + pw;
      if (nxt <= n && sum + bt[nxt] < x) { // for upper bound (sum + bt[nxt] <= x)
        sum += bt[nxt];
        idx = nxt;
      }
    }
    return idx + 1;
  }

};
