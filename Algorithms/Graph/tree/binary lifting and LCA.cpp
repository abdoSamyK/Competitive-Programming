/* (binary lifting & lowest common ancestor(lca))
 * 1-indexed, dfs(1, 0)
 * if(k-th ancestor = 0) no such that ancestor,
 * O(n log(n))
 * O(log(n)) per query
 */
const int N = 2e5 + 5;
const int lg = 20;
vector<int> adj[N];
int up[N][lg];
int dep[N];
int n;
void dfs(int u, int p) { // build depth + build up
  up[u][0] = p;
  for (int j = 1;j < lg;++j) {
    up[u][j] = up[up[u][j - 1]][j - 1];
  }
  for (auto v : adj[u]) {
    if (v == p) continue;
    dep[v] = dep[u] + 1;
    dfs(v, u);
  }
}

int kth(int u, int k) { // binary lifting
  for (int j = 0;j < lg;++j) {
    if (k & (1 << j)) {
      u = up[u][j];
      if (u == 0) break; // no such that ancestor
    }
  }
  return u;
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  int dif = dep[u] - dep[v];
  u = kth(u, dif);

  if (u == v) return u;

  for (int j = lg - 1;j >= 0;--j) {
    if (up[u][j] != up[v][j]) {
      u = up[u][j];
      v = up[v][j];
    }
  }
  return up[u][0];
}
// number of edges between u and v
int dist(int u, int v) {
  int l = lca(u, v);
  return dep[u] + dep[v] - (dep[l] * 2);
}
// k-th node on the path from u to v (0-th node = u)
int kth_lca(int u, int v, int k) {
  int l = lca(u, v);
  int d = dep[u] + dep[v] - (dep[l] * 2);

  if (k > d) return 0;

  if (dep[l] + k <= dep[u]) return kth(u, k);
  k -= (dep[u] - dep[l]);
  return kth(v, dep[v] - dep[l] - k);
}