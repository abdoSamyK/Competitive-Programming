static const int N = 1e5 + 5;
vector<int> adj[N];
bool visited[N];
vector<int> path;
int from, to;

/*
 * DFS to find any path (from -> to)
 * return true if path exists
 */
bool dfs(int u) {
  visited[u] = true;

  if (u == to) {
    path.emplace_back(u);
    return true;
  }

  for (int v : adj[u]) {
    if (!visited[v]) {
      if (dfs(v)) {
        path.emplace_back(u);
        return true;
      }
    }
  }
  return false;
}

void solve() {

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].emplace_back(b);
    adj[b].emplace_back(a); // remove for directed graph
  }

  cin >> from >> to;

  if (dfs(from)) {
    reverse(path.begin(), path.end());
    for (int x : path) cout << x << ' ';
    cout << '\n';
  } else {
    cout << "No path found\n";
  }

}
