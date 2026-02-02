/*
 * Topological Sort using dfs
 */
const int N = 1e5 + 5;
vector<int> adj[N];
int vis[N];          // 0 = unvisited, 1 = visiting, 2 = done
vector<int> topo;
bool cycle; // to detect cycle(if there -> can't find topological sort)

void dfs(int v) {
  vis[v] = 1;
  for (int u : adj[v]) {
    if (vis[u] == 0) {
      dfs(u);
      if (cycle) return;
    }
    else if (vis[u] == 1) {
      cycle = true;
      return;
    }
  }
  vis[v] = 2;
  topo.push_back(v);
}

int n;
void topological_sort() {
  cycle = false;
  for (int i = 1; i <= n; ++i) {
    if (vis[i] == 0) {
      dfs(i);
    }
  }
  reverse(topo.begin(), topo.end());
}
