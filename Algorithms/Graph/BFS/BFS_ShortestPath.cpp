const int N = 1e5 + 5;
vector<int> adj[N];

/*
 * BFS (shortest path)
 * unweighted undirected graph(1-based nodes)
 */
void BFS() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int start;
  cin >> start;

  vector<int> distance(n + 1, -1);
  queue<int> q;

  distance[start] = 0;
  q.push(start);

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (distance[v] == -1) {
        distance[v] = distance[u] + 1;
        q.push(v);
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    if (distance[i] != -1)
      cout << "Shortest path from " << start << " to " << i << " is " << distance[i] << '\n';
    else
      cout << "Node " << i << " is not reachable from " << start << '\n';
  }
}