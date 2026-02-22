/*dijkstra on segment tree
 * addedge foreach [e, l, r, cost]
 * O((V + E log V) log V)
 */
ll INF = 1e18;
int seg_size;
vector<vector<pair<int, ll>>> adj;
void init(int n) {
  seg_size = 1;
  while (seg_size < n) seg_size *= 2;
  adj.assign(2 * seg_size, vector<pair<int, ll>>());
  for(int x = 0; x <= seg_size - 2; x++) {
    adj[x].emplace_back(2 * x + 1, 0);
    adj[x].emplace_back(2 * x + 2, 0);
  }
}
void addedge(int u, int l , int r, ll w, int x, int lx, int rx) {
  if (lx >= r || rx <= l) return;
  if (lx >= l && rx <= r) {
    int uleaf = (seg_size - 1) + u;
    adj[uleaf].emplace_back(x, w);
    return;
  }
  int m = (lx + rx) / 2;
  addedge(u, l, r, w, 2 * x + 1, lx, m);
  addedge(u, l, r, w, 2 * x + 2, m, rx);
}
void dijkstra(int st, vector<ll> &dis , vector<int> &par) {
  int n = adj.size();
  dis.assign(n, INF);
  par.assign(n, -1);

  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
  pq.emplace(0, st);
  dis[st] = 0;
  while (!pq.empty()) {
    ll du = pq.top().first;
    int u = pq.top().second;
    pq.pop();

    if (du > dis[u]) continue;

    for (auto [v, w] : adj[u]) {
      ll dv = du + w;
      if (dv < dis[v]) {
        dis[v] = dv;
        par[v] = u;
        pq.emplace(dv, v);
      }
    }
  }
}
vector<int> path;
void restore_path(int _st, int _end, vector<int> &par) {
  int st = (seg_size - 1) + _st;
  int end = (seg_size - 1) + _end;
  if (par[end] == -1 && st != end) return;
  for (int v = end; v != -1;v = par[v]) {
    if (v >= seg_size - 1) {
      path.emplace_back(v - (seg_size - 1));
    }
  }
  reverse(path.begin(), path.end());
}