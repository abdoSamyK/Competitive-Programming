struct node {
  ll ini = 0, val, lazyset, lazyadd;
  bool islazyset, islazyadd;

  node() : val(ini), lazyset(0), lazyadd(0), islazyset(false), islazyadd(false) {}
  node(ll x) : val(x), lazyset(0), lazyadd(0), islazyset(false), islazyadd(false) {}



  // (&who affected by who)?
  void add(ll va, int lx, int rx) {
    val = (val + ((rx - lx) * va));
    lazyadd += va;
    islazyadd = true;
  }
  void set(ll va, int lx, int rx) {
    val = ((rx - lx) * va);
    lazyset = va;
    islazyset = true;
    lazyadd = 0;
    islazyadd = 0;
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
    return node(a.val + b.val);
  }

  // who must be first (&who affected by who)? (here set first)
  void propagate(int x, int lx, int rx) {
    if (rx - lx == 1) return;

    if (values[x].islazyset) {
      int m = (lx + rx) / 2;
      values[2 * x + 1].set(values[x].lazyset, lx, m);
      values[2 * x + 2].set(values[x].lazyset, m, rx);
      values[x].islazyset = false;
      values[x].lazyset = 0;
    }
    if (values[x].islazyadd) {
      int m = (lx + rx) / 2;
      values[2 * x + 1].add(values[x].lazyadd, lx, m);
      values[2 * x + 2].add(values[x].lazyadd, m, rx);
      values[x].islazyadd = false;
      values[x].lazyadd = 0;
    }
  }
  void build(vector<ll> &v, int x, int lx, int rx) {
    if(rx - lx == 1) {
      if(lx < (int)v.size())
        values[x] = node(v[lx]);
      return;
    }
    int m = (lx + rx) / 2;
    build(v, 2 * x + 1, lx, m);
    build(v, 2 * x + 2, m, rx);
    values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
  }
  void build(vector<ll> &v) {
    build(v, 0, 0, size);
  }
  void set (int l, int r, ll val, int x, int lx, int rx) {
    propagate(x, lx, rx);
    if(lx >= r || l >= rx) return;
    if (lx >= l && rx <= r) {
      values[x].set(val, lx, rx);
      return;
    }
    int m = (lx + rx) / 2;
    set(l, r, val, 2 * x + 1, lx, m);
    set(l, r, val, 2 * x + 2, m, rx);
    values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
  }
  void set(int l, int r, ll val) {
    set(l, r, val, 0, 0, size);
  }

  void add (int l, int r, ll val, int x, int lx, int rx) {
    propagate(x, lx, rx);
    if(lx >= r || l >= rx) return;
    if (lx >= l && rx <= r) {
      values[x].add(val, lx, rx);
      return;
    }
    int m = (lx + rx) / 2;
    add(l, r, val, 2 * x + 1, lx, m);
    add(l, r, val, 2 * x + 2, m, rx);
    values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
  }
  void add(int l, int r, ll val) {
    add(l, r, val, 0, 0, size);
  }

  node get(int l, int r, int x, int lx, int rx) {
    propagate(x, lx, rx);
    if(lx >= r || l >= rx) return node();
    if(lx >= l && rx <= r) return values[x];   // return node
    int m = (lx + rx) / 2;
    node s1 = get(l, r, 2 * x + 1, lx, m);
    node s2 = get(l, r, 2 * x + 2, m, rx);
    return merge(s1, s2);
  }
  node get(int l, int r) {
    return get(l, r, 0, 0, size);
  }
};