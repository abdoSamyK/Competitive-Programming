/**
* euler tour technique(tree flattening) (0-based)
 * in[i] start of subtree
 * out[i] : last node in subtree
 * Range : [in[i], out[i]]
 * Size : out[i] - in[i] + 1
 */
const int N = 2e5 + 5;
vector<int> adj[N];
int in[N], out[N];
vector<int> flat_tree;
int cnt = 0;
void dfs(int u, int par) {
  in[u] = cnt++;
  flat_tree.emplace_back(u);
  for (auto v : adj[u]) {
    if (v == par) continue;
    dfs(v, u);
  }
  out[u] = cnt - 1;
}