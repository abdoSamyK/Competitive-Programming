struct node {
    ll ini = 0, val;
    // initialize with neutral value
    node() : val(ini) {} // neutral
    // initialize with a given value
    node(ll x) : val(x) {}
    // Update the (node) with a new value
    void update(ll x) {
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
        return node(a.val + b.val); // operation -> (+, min, max, gcd, ...)
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
    void set (int i, ll val, int x, int lx, int rx) {
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
    void set(int i, ll val) {
        set(i, val, 0, 0, size);
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