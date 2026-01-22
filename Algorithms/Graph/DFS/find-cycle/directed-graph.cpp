const int N = 1e5 + 5;
vector<int> adj[N];
vector<int> color;
vector<int> path;
vector<int> cycle;

/*
 * DFS to detect a cycle in connected directed graph
 */
void dfs(int u) {
  color[u] = 1;                // currently visiting
  path.push_back(u);

  for (int v : adj[u]) {
    if (color[v] == 0) {
      dfs(v);
    } else if (color[v] == 1) {
      if (cycle.empty()) {
        for (int i = path.size() - 1; i >= 0; i--) {
          cycle.push_back(path[i]);
          if (path[i] == v) break;
        }
      }
    }
  }

  path.pop_back();
  color[u] = 2;   // fully processed
}

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) adj[i].clear();
  color.assign(n + 1, 0);
  path.clear();
  cycle.clear();

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }

  dfs(1);

  if (!cycle.empty()) {
    reverse(cycle.begin(), cycle.end());
    cout << "cycle found\n";
    for (int x : cycle) cout << x << ' ';
    cout << '\n';
  } else {
    cout << "cycle not found\n";
  }
}
