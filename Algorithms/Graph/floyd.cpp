#define ll long long
const ll INF = 1e18;

void get_path(int u, int v, vector<vector<int>>& p, vector<int>& path) {
  int k = p[u][v];
  if (k == -1) {
    path.push_back(v);
    return;
  }
  get_path(u, k, p, path);
  get_path(k, v, p, path);
}
/*
 * floyd algorithm with path reconstruction
 * dis[i][j] = shortest path from i to j
 * p[i][j] = splitter of the shortest path from i to j
 * p[i][i] = -1 (no splitter)
 */
void floyd() {
  int n, m;
  cin >> n >> m;
  vector<vector<ll>> dis(n, vector<ll>(n, INF));
  vector<vector<int>> p(n, vector<int>(n, -1));
  for (int i = 0; i < n; i++) dis[i][i] = 0;
  for (int i = 0; i < m; i++) {
    int u, v;
    ll w;
    cin >> u >> v >> w; // no multiple edges
    u--, v--;
    dis[u][v] = w;
    dis[v][u] = w; // undirected graph
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dis[i][k] < INF && dis[k][j] < INF) {
          if (dis[i][k] + dis[k][j] < dis[i][j]) {
            dis[i][j] = dis[i][k] + dis[k][j];
            p[i][j] = k; // k is splitter
          }
        }
      }
    }
  }
}

