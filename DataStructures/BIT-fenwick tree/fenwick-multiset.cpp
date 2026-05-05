template<class T = ll>
struct myMultiset { // 1-based
  int n = 1e6 + 3;
  vector<T> bt;
  int lg;

  myMultiset() {
    bt.assign(n + 1, 0);
    lg = 1;
    while ((lg << 1) <= n) lg <<= 1;
  }

  T lowbit(int x) {
    return x & -x;
  }

  void add(int idx, T val) {
    if (idx <= 0) return;
    while (idx <= n) {
      bt[idx] += val;
      idx += lowbit(idx);
    }
  }

  T get(int idx) {
    T ans = 0;
    while (idx > 0) {
      ans += bt[idx];
      idx -= lowbit(idx);
    }
    return ans;
  }

  T get_idx(int idx) { // how many times the value idx appears in the multiset.
    return get(idx) - get(idx - 1);
  }

  T get_range(int l, int r) { // number of elements in [l, r]
    return get(r) - get(l - 1);
  }

  void set(int idx, T val) {
    T old = get_idx(idx);
    add(idx, val - old);
  }

  int lower_bound(T x) {
    T sum = 0;
    int idx = 0;

    for (int pw = lg; pw > 0; pw >>= 1) {
      int nxt = idx + pw;
      if (nxt <= n && sum + bt[nxt] < x) {
        sum += bt[nxt];
        idx = nxt;
      }
    }
    return idx + 1;
  }

  void insert(int va, T cnt = 1) {
    add(va, cnt);
  }

  void erase(int va, T cnt = 1) {
    cnt = min(cnt, get_idx(va));
    if (cnt > 0) add(va, -cnt);
  }

  int kth(T k) { // val of k-th smallest element (1-based) (1, 2, 3, 3) -> kth(4) = 3
    if (k <= 0 || k > get_sz()) return -1; // kth(5) = -1
    return lower_bound(k);
  }
  T get_sz() { // total number of elements in the multiset
    return get(n);
  }
};