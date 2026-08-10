/**
 * longest increasing subsequence in given array
 *------------------------------------------------
 * dp[i] = dp[j] + 1 > such that a[i] > a[j] and j before i
 * so dp[i] can link to dp[j]
 * the best way is that dp[i] line with the max number before it
 *  (when take number add it in the segment tree to get the max before)
 *    using segment tree
 */
struct node {
  int ini = 0, val;
  node() : val(ini) {}
  node(int x) : val(x) {}
  void update(int x) {
    val = x;
  }
};
struct segtree {
  // 0-indexed,r not included ==> [l, r)
  int size;
  vector<node> values;
  void init(int n) {
    size = 1;
    while(size < n) size *= 2;
    values.assign(2 * size, node());
  }
  node merge(const node &a, const node &b) {
    return node(max(a.val, b.val));
  }
  void set (int i, int val, int x, int lx, int rx) {
    if(rx - lx == 1) {
      values[x].update(val);
      return;
    }
    int m = (lx + rx) / 2;
    if(i < m) {
      set(i, val, 2 * x + 1, lx, m);
    }
    else {
      set(i, val, 2 * x + 2, m, rx);
    }
    values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
  }
  void set(int i, int val) {
    set(i, val, 0, 0, size);
  }
  node get(int l, int r, int x, int lx, int rx) {
    if(lx >= r || l >= rx) return node();
    if(lx >= l && rx <= r) return values[x];
    int m = (lx + rx) / 2;
    node s1 = get(l, r, 2 * x + 1, lx, m);
    node s2 = get(l, r, 2 * x + 2, m, rx);
    return merge(s1, s2);
  }
  node get(int l, int r) {
    return get(l, r, 0, 0, size);
  }
};


void LIS() { //
  int n;cin >> n;
  vector<int> v(n), ids;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    ids.push_back(v[i]);
  }
  sort(ids.begin(), ids.end());
  ids.erase(unique(ids.begin(), ids.end()), ids.end());
  auto get_id= [&](int idx) {
    return lower_bound(ids.begin(), ids.end(), v[idx]) - ids.begin();
  };

  segtree st;
  st.init(ids.size() + 1);

  vector<int> dp(n);
  for (int i = 0;i < n;++i) {
    dp[i] = st.get(0, get_id(i)).val + 1;
    st.set(get_id(i), dp[i]);
  }

  cout << *max_element(dp.begin(), dp.end());
}
