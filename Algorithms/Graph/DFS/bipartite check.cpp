const int N = 2e5 + 5;

vector<int> adj[N];
int color[N]; // -1 = unvisited, 0/1 = colors

bool dfs(int u, int c) {
  color[u] = c;

  for (int v : adj[u]) {
    if (color[v] == -1) {
      if (!dfs(v, c ^ 1))
        return false;
    }
    else if (color[v] == c) {
      return false;
    }
  }

  return true;
}
bool is_bipartite(int n) {
  memset(color, -1, sizeof(color));

  for (int i = 1; i <= n; i++) {
    if (color[i] == -1) {
      if (!dfs(i, 0))
        return false;
    }
  }

  return true;
}