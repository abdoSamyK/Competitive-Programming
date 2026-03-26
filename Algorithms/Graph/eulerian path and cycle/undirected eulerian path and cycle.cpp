const int N = 2e5 + 5, M = 2e5 + 5;
int n, m;
vector<pair<int, int>> adj[N];
vector<int> path; // tour
int deg[N];
int ptr[N];
bool used[M]; // edge_id used?
int eid = 0;
bool cycle = false;

void clr() { // for testcases(nodes)
  for (int i = 1;i <= n;++i) {
    adj[i].clear();
    deg[i] = 0;
    ptr[i] = 0;
  }
  for (int i = 0;i <= m;++i) used[i] = false;
  path.clear();
  eid = 0;
  cycle = false;
}

void addedge(int u, int v) {
  adj[u].emplace_back(v, eid);
  adj[v].emplace_back(u, eid);
  deg[u]++, deg[v]++;
  eid++;
}

void dfs(int u) {
  while (ptr[u] < adj[u].size()) { // to start after last stoped edge
    auto[v, id] = adj[u][ptr[u]++];
    if (used[id]) continue;
    used[id] = true;
    dfs(v);
  }
  path.emplace_back(u);
}

bool euler() {  // O(E)

  vector<int> odd;
  int st = -1;
  for (int i = 1;i <= n;++i) {
    if (deg[i] % 2 == 1) {
      odd.emplace_back(i);
    }
    if (st == -1 && deg[i] > 0) st = i;
  }

  if (!(odd.size() == 0 || odd.size() == 2)) {
    return false;
  }
  if (odd.size() == 2) st = odd[0];
  else cycle = true;

  if (st == -1) return true; // all nodes are separate...

  dfs(st);
  if (path.size() != eid + 1) { // > one component.
    return false;
  }
  reverse(path.begin(), path.end());
  return true;}
void solve() {
  cin >> n >> m;
  clr();
  for (int i = 1;i <= m;++i) {
    int u, v;cin >> u >> v;
    addedge(u, v);
  }
  if (!euler()) {
    cout << -1;
  } else {
    for (auto i : path) cout << i << ' ';
    cout << '\n';
  }
}
