const int N = 200005;
vector<int> adj[N];
int n;
int farthestNode, maxDist;
void dfs(int u, int parent, int dist) {
  if (dist > maxDist) {
    maxDist = dist;
    farthestNode = u;
  }
  for (int v : adj[u]) {
    if (v == parent) continue;
    dfs(v, u, dist + 1);
  }
}
void diameter() {
  maxDist = -1;
  dfs(1, -1, 0);   // first DFS from any node
  int A = farthestNode;

  maxDist = -1;
  dfs(A, -1, 0);   // second DFS from A
  // diameter = maxDist;
}