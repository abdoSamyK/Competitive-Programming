/*
* set => v[i] = v[i]/x  ;v[i] >= 0, x >= 0
 * get the sum of a range [l, r)
 */
struct node {
  ll ini = 0, mx, val;
  node() : val(ini), mx(ini) {}
  node(ll x) : val(x), mx(x) {}
  void update(ll x) {
    val /= x;
    mx /= x;
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
    node c;
    c.val = a.val + b.val;
    c.mx = max(a.mx,  b.mx);
    return c;
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
    if(lx >= r || l >= rx || values[x].mx == 0) return;
    if(rx - lx == 1) {
      values[x].update(val);
      return;
    }
    int m = (lx + rx) / 2;
    set(l, r, val, 2 * x + 1, lx, m);
    set(l, r, val, 2 * x + 2, m, rx);

    values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
  }
  void set(int l, int r, ll val) {
    if (val == 1) return;
    set(l, r, val, 0, 0, size);
  }
  node get(int l, int r, int x, int lx, int rx) {
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