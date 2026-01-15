/* (Dijkstra's Algorithm + Path Reconstruction)
* s: source node (0-based)
* n: number of nodes
* adj: adjacency list of graph
* d: vector to store shortest distances from s
* p: parent array to store the path tree(initialize with -1)
*/
#define ll long long
const ll INF = 1e18;
void dijkstra(int s, int n, const vector<vector<pair<int, int>>>& adj, vector<ll> &d, vector<int> &p) {
  d.assign(n, INF);
  d[s] = 0;

  // {dist, node}
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
  pq.emplace(0, s);

  while (!pq.empty()) {
    ll du = pq.top().first;
    int u = pq.top().second;
    pq.pop();

    if (du > d[u]) continue;

    for (auto [v, w] : adj[u]) {
      ll dv = du + w;
      if (dv < d[v]) { // Relaxation Step
        d[v] = dv;
        p[v] = u; // Update parent
        pq.emplace(dv, v);
      }
    }
  }
}
// restore the path from (source -> target)
vector<int> restore_path(int s, int t, const vector<int>& p) {
  // If no path exists
  if (p[t] == -1 && s != t) {
    return {}; // Return empty path
  }

  vector<int> path;
  for (int v = t; v != -1; v = p[v]) {
    path.push_back(v); //
  }
  reverse(path.begin(), path.end());
  return path;
}