/*
 * get the sum at range and add value to range
 */
struct node {
  ll ini = 0, val, lazy;
  bool isLazy;

  node() : val(ini), lazy(0), isLazy(false) {}
  node(ll x) : val(x), lazy(0), isLazy(false) {}

  void update(ll x, int lx, int rx) {
    val += x * (rx - lx);
    lazy += x;
    isLazy = true;
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
    return node(a.val + b.val); // (+, min, max, gcd, ...)
  }
  void propagate(int x, int lx, int rx) {
    if (rx - lx == 1 || !values[x].isLazy) return;
    int m = (lx + rx) / 2;
    values[2 * x + 1].update(values[x].lazy, lx, m);
    values[2 * x + 2].update(values[x].lazy, m, rx);
    values[x].isLazy = false;
    values[x].lazy = 0;
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
      values[x].update(val, lx, rx);
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