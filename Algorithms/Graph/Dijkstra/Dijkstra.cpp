/*
* s: source node (0-based)
* n: number of nodes
* adj: adjacency list of graph
* d: vector to store shortest distances from s
*/
#define ll long long
const ll INF = 1e18;
void dijkstra(int s, int n, const vector<vector<pair<int, int>>>& adj, vector<ll> &d) {
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
        pq.emplace(dv, v);
      }
    }
  }
}