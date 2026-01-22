const int N = 1e5 + 5;
vector<int> adj[N];
bool visited[N];
vector<int> path;
vector<int> cycle;

/*
 * DFS to detect a cycle in connected undirected graph
 */
void dfs(int u, int parent) {
  visited[u] = true;
  path.push_back(u);

  for (int v : adj[u]) {
    if (v == parent) continue;
    if (!visited[v]) {
      dfs(v, u);
    } else {
      if (cycle.empty()) {
        for (int i = path.size() - 1; i >= 0; i--) {
          cycle.push_back(path[i]);
          if (path[i] == v) break;
        }
      }
    }
  }
  path.pop_back();
}

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, -1);

  if (!cycle.empty()) {
    cout << "cycle found\n";
    for (int x : cycle) cout << x << ' ';
    cout << '\n';
  } else {
    cout << "cycle not found\n";
  }
}