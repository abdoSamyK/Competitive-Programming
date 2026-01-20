#define ll long long
struct Edge {
  int u, v, w;
  bool operator<(const Edge &e) const {
    return w < e.w;
  }
};

struct DSU {
  vector<int> par, sz;

  DSU(int n) {
    par.resize(n + 1);
    sz.resize(n + 1, 1);
    iota(par.begin(), par.end(), 0); // make each node its own parent
  }

  int find_set(int v) {
    if (par[v] == v) return v;
    return par[v] = find_set(par[v]);
  }

  bool union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (sz[a] < sz[b]) swap(a, b); // Union by size
      par[b] = a;
      sz[a] += sz[b];
      return true;
    }
    return false;
  }
};

/*
 * n Number of nodes
 * edges Vector of Edge structs
 */
ll kruskal(int n, vector<Edge>& edges) {
  sort(edges.begin(), edges.end());

  DSU dsu(n);
  ll mst_cost = 0;
  int edges_count = 0; // n-1 or not connected graph

  for (auto e : edges) {
    if (dsu.union_sets(e.u, e.v)) {
      mst_cost += e.w;
      edges_count++;
    }
  }
  if (edges_count != n - 1) return -1;
  return mst_cost;
}