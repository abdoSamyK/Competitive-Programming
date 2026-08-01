/*
 * find a cycle in => directed graph
 * return true if a cycle exists and stores one cycle in 'cycle'.
 */

const int N = 1e5 + 5;
int n;
vector<int> adj[N];
int color[N];      // 0 = unvisited, 1 = visiting, 2 = done
int parent[N];
int cycle_start, cycle_end;
vector<int> cycle;

bool dfs(int u) {
  color[u] = 1;

  for (int v : adj[u]) {
    if (!color[v]) {
      parent[v] = u;
      if (dfs(v)) return true;
    }
    else if (color[v] == 1) {
      cycle_start = v;
      cycle_end = u;
      return true;
    }
  }

  color[u] = 2;
  return false;
}

bool find_cycle() {
  fill(color, color + n + 1, 0);
  fill(parent, parent + n + 1, -1);

  cycle.clear();
  cycle_start = cycle_end = -1;

  for (int i = 1; i <= n; i++)
    if (!color[i] && dfs(i))
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