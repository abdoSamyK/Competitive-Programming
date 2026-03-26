const int N = 2e5 + 5;
int n, m;
vector<int> adj[N];
vector<int> path; // tour
int indeg[N], outdeg[N];
int ptr[N];
int eid = 0;
bool cycle = false;
void clr() { // for testcases(nodes)
  for (int i = 1;i <= n;++i) {
    adj[i].clear();
    indeg[i] = outdeg[i] = 0;
    ptr[i] = 0;
  }
  path.clear();
  eid = 0;
  cycle = false;
}

void addedge(int u, int v) {
  adj[u].emplace_back(v);
  outdeg[u]++, indeg[v]++;
  eid++;
}

void dfs(int u) {
  while (ptr[u] < adj[u].size()) { // to start after last stoped edge
    auto v = adj[u][ptr[u]++];
    dfs(v);
  }
  path.emplace_back(u);
}

bool euler() {  //O(E)

  int st = -1, sttmp = -1;
  int in = 0, out = 0;
  for (int i = 1;i <= n;++i) {
    if (indeg[i] - outdeg[i] == 1) in++;
    else if (indeg[i] - outdeg[i] == -1) out++, st = i;
    else if (indeg[i] != outdeg[i]) {
      return false;
    } else if (outdeg[i] > 0) {
      sttmp = i;
    }
  }

  if (!((in == 0 && out == 0) || (in == 1 && out == 1))) {
    return false;
  }

  if (st == -1) { // all nodes are separate...
    if (sttmp == -1) {
      return true;
    }
    st = sttmp;
    cycle = true;
  }

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