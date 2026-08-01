/*
 * topological Sort (DFS)
 * false if a cycle exists.
 */
const int N = 1e5 + 5;

vector<int> adj[N];
vector<int> topo;
int vis[N]; // 0 = unvisited, 1 = visiting, 2 = done
bool cycle;
int n;

void dfs(int u) {
  vis[u] = 1;

  for (int v : adj[u]) {
    if (!vis[v]) {
      dfs(v);
      if (cycle) return;
    }
    else if (vis[v] == 1) {
      cycle = true;
      return;
    }
  }

  vis[u] = 2;
  topo.push_back(u);
}

bool topo_sort() {
  topo.clear();
  fill(vis, vis + n + 1, 0);
  cycle = false;

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i);
      if (cycle) return false;
    }
  }

  reverse(topo.begin(), topo.end());
  return true;
}

