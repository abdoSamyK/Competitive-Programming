/*
 * Topological Sort using bfs
 * Kahn's algorithm
 */
int n;
bool cycle
const int N = 1e5 + 5;
vector<int> adj[N];
vector<int> topo;


void topological_sort() {
  vector<int> indegree(n + 1);
  for (int i = 1; i <= n; ++i) {
    for (int j : adj[i]) {
      indegree[j]++;
    }
  }
  queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (indegree[i] == 0) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int u = q.front();q.pop();
    topo.push_back(u);
    for (int v : adj[u]) {
      indegree[v]--;
      if (indegree[v] == 0) {
        q.push(v);
      }
    }
  }
  cycle = (topo.size() != n);
}
