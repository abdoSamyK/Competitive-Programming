/**(small to large , dsu on trees, sack)
 * each node have color
 * for each query > calculate the number of nodes with value x in the subtree of node s
*/
const int N = 2e5 + 5;
vector<int> adj[N];

// Tree properties
int sz[N], big[N], col[N];

// ==========================================
// [1] data structures (used for each node)
int freq[N];  // freq[c] = frequency of color 'c' in the current subtree
int ans[N];   // ans[i] = the answer to the i-th query

// queries[u] stores pairs of {target_color, query_index}
vector<pair<int, int>> queries[N];


// ==========================================
// (Size & Heavy Child)
void dfs_sz(int u, int p = 0) {
    sz[u] = 1;
    big[u] = 0;
    int max_sub = 0;

    for (int v : adj[u]) {
        if (v != p) {
            dfs_sz(v, u);
            sz[u] += sz[v];

            // Identify the heavy child
            if (sz[v] > max_sub) {
                max_sub = sz[v];
                big[u] = v;
            }
        }
    }
}


// ==========================================
// add and remove a single node contribution
void upd(int u, int d) {
    // Add or remove the frequency of the current node's color
    freq[col[u]] += d;
}


// ==========================================
// subtree traversal (for light children)
void collect(int u, int p, int d) {
    upd(u, d);
    for (int v : adj[u]) {
        if (v != p) {
            collect(v, u, d);
        }
    }
}


// ==========================================
// sack logic
void dfs_sack(int u, int p, bool keep) {
    //  1: Process light children and discard their data
    for (int v : adj[u]) {
        if (v != p && v != big[u]) {
            dfs_sack(v, u, false);
        }
    }

    //  2: Process the heavy child and KEEP its data
    if (big[u] != 0) {
        dfs_sack(big[u], u, true);
    }

    //  3: Add the current node...
    upd(u, 1);

    // ... re-add the light children's data
    for (int v : adj[u]) {
        if (v != p && v != big[u]) {
            collect(v, u, +1);
        }
    }

    //  4: ANSWER OFFLINE QUERIES for subtree 'u'
    for (auto [x, q_idx] : queries[u]) {
        ans[q_idx] = freq[x];
    }

    //  5: If this node is a light child, clear it from the global data structure
    if (!keep) {
        collect(u, p, -1);
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> col[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= q; i++) {
        int u, x;
        cin >> u >> x;
        queries[u].push_back({x, i});
    }
    dfs_sz(1, 0);
    dfs_sack(1, 0, true);
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
}