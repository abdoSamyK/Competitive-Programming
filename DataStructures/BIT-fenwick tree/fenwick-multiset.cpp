
struct myMultiset { // 1-based Fenwick Tree Multiset
  int n;
  vector<int> bt;
  int lg;

  myMultiset(int _n) {
    n = _n;
    bt.assign(n + 1, 0);
    lg = 1;
    while ((lg << 1) <= n) lg <<= 1;
  }

  int lowbit(int x) { // return least significant set bit
    return x & -x;
  }

  void add(int idx, int val = 1) { // add val to the frequency of value idx
    if (idx <= 0) return;
    while (idx <= n) {
      bt[idx] += val;
      idx += lowbit(idx);
    }
  }

  int get(int idx) { // return number of elements with value <= idx (prefix sum)
    int ans = 0;
    while (idx > 0) {
      ans += bt[idx];
      idx -= lowbit(idx);
    }
    return ans;
  }

  int get_idx(int idx) { // returns how many times value idx appears
    return get(idx) - get(idx - 1);
  }

  int get_range(int l, int r) { // returns the number of elements in [l, r]
    return get(r) - get(l - 1);
  }

  void set(int idx, int val) { // sets the frequency of value idx to val
    int old = get_idx(idx);
    add(idx, val - old);
  }

  void insert(int val, int cnt = 1) { // inserts cnt copies of val
    add(val, cnt);
  }

  void erase(int val, int cnt = 1) { // removes up to cnt copies of val
    cnt = min(cnt, get_idx(val));
    if (cnt > 0) add(val, -cnt);
  }

  int get_sz() { // returns the total number of elements
    return get(n);
  }

  int kth(int k) { // returns the value of the k-th smallest element (1-based)
                  // e.g. {1,2,3,3} -> kth(4)=3
                  // returns -1 if k is invalid
    if (k <= 0 || k > get_sz()) return -1;

    int idx = 0;
    for (int pw = lg; pw; pw >>= 1) {
      int nxt = idx + pw;
      if (nxt <= n && bt[nxt] < k) {
        idx = nxt;
        k -= bt[nxt];
      }
    }
    return idx + 1;
  }

  int order_of_key(int val) { // number of elements strictly less than val
    return get(val - 1);
  }

  int lower_bound(int val) { // first element >= val, or -1 if none exists
    int cnt = get(val - 1);
    if (cnt == get_sz()) return -1;
    return kth(cnt + 1);
  }

  int upper_bound(int val) { // first element > val, or -1 if none exists
    int cnt = get(val);
    if (cnt == get_sz()) return -1;
    return kth(cnt + 1);
  }

  bool contains(int val) { // returns true if val exists
    return get_idx(val) > 0;
  }

  void clear() { // removes all elements
    fill(bt.begin(), bt.end(), 0);
  }
};
