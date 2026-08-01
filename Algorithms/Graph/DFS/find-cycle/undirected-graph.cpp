/*
 * find a cycle in an undirected graph
 * return true if a cycle exists and stores one cycle in 'cycle'
 */

const int N = 1e5 + 5;
int n;
vector<int> adj[N];
bool vis[N];
int parent[N];
int cycle_start, cycle_end;
vector<int> cycle;

bool dfs(int u, int p = -1) {
  vis[u] = true;

  for (int v : adj[u]) {
    if (v == p) continue;

    if (!vis[v]) {
      parent[v] = u;
      if (dfs(v, u)) return true;
    }
    else {
      cycle_start = v;
      cycle_end = u;
      return true;
    }
  }

  return false;
}

bool find_cycle() {
  fill(vis, vis + n + 1, false);
  fill(parent, parent + n + 1, -1);

  cycle.clear();
  cycle_start = cycle_end = -1;

  for (int i = 1; i <= n; i++)
    if (!vis[i] && dfs(i))
      break;

  if (cycle_start == -1)
    return false;

  cycle.push_back(cycle_start);
  for (int v = cycle_end; v != cycle_start; v = parent[v])
    cycle.push_back(v);
  cycle.push_back(cycle_start);

  reverse(cycle.begin(), cycle.end());
  return true;
}