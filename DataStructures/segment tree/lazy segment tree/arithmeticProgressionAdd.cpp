
/* (segment tree(add at range with fixed increasing val)
 * the trick is :
 *  you have sequence and for each number at range you want to add numbers with (fixed(same) difference)
 *  (x) , (x + d), (x + d + d) , ...
 *  -> you have start , difference
 *  let (start = x, diff = d)
 *  now for : a1, a2, a3, a4
 *            +x, +x, +x, +x
 *         *  0d, 1d, 2d, 3d  -> d(0 + 1 + 2 + 3....)
 *  let len = (rx - lx)
 *  so the new sum is : sum = sum + ((len * x) + (d * (len) * (len - 1) / 2)
 *  ---------------------------------------------------------------------------
 *  the second thing how to merge to lazy by use (+ or * or both or other thing and so on. ... )
 *  i have at the first the sum :
 *    sum = (a1 + x) + (a2 + x + d) + (a3 + x + (2*d)) ....
 *    nsum = (a1 + x + nx) + (a2 + x + nx + d + nd) + (a3 + x + nx + (2*d) + (2*nd))
 *         = (len * (x + nx)) + ((len * (len - 1) / 2) * (d + nd)) + (a1 + a2 + a3)
 *   -> i have len so i will use only :
 *   so the new x = (x + nx), new dif = (d + nd) ...
 *  ---------------------------------------------------------------------------
 *  what about set and propagate for the two half's,,,
 *  for propagate :
 *  for the left half -> (same x, same d)
 *  for the right half -> (x + ((mid - l)) * (d), same d)
 *  -----------
 *  for se and return all value...
 *  (x + (xl - x) * d)
 *
 */
struct node {
  ll ini = 0, val, lazyx, lazyd;
  bool isLazy;

  node() : val(ini), lazyx(0), lazyd(0), isLazy(false) {}
  node(ll x) : val(x), lazyx(0), lazyd(0), isLazy(false) {}

  void update(ll x, ll d, int lx, int rx) {
    ll len = rx - lx;
    val = val + (len * x) + d * (len * (len - 1) / 2);
    lazyx += x;
    lazyd += d;
    isLazy = true;
  }
};

struct segtree {
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
    values[2 * x + 1].update(values[x].lazyx, values[x].lazyd, lx, m);
    values[2 * x + 2].update(values[x].lazyx + ((m - lx) * values[x].lazyd), values[x].lazyd, m, rx);
    values[x].isLazy = false;
    values[x].lazyx = values[x].lazyd = 0;
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
  void set (int l, int r, ll va, ll dif, int x, int lx, int rx) {
    propagate(x, lx, rx);
    if(lx >= r || l >= rx) return;
    if (lx >= l && rx <= r) {
      values[x].update(va + 1ll * (lx - l) * (dif), dif, lx, rx);
      return;
    }
    int m = (lx + rx) / 2;
    set(l, r, va, dif, 2 * x + 1, lx, m);
    set(l, r, va, dif, 2 * x + 2, m, rx);
    values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
  }
  void set(int l, int r, ll va, ll dif) {
    set(l, r, va, dif, 0, 0, size);
  }
  node get(int l, int r, int x, int lx, int rx) {
    propagate(x, lx, rx);
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
