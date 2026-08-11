/**
* Dynamic Graph Heavy-Light Degree (SQRT Decomposition)
* problem: Track online/offline status, add/remove edges, count online friends.
*  'O' u -> make node u online
*  'f' u -> make node u offline
*  'A' u v -> make u, v friends
*  'D' u v -> make u, v unfriends
*  'C' u -> count online friends for node u.
------------------------------------------------------
* N <= 50000, m <=150000, q <= 250000
*  O(Q * sqrt(N + Q))
*/


const int N = 5e4 + 5;
const int SQ = 800; // Threshold: approx sqrt(Max total edge operations)

vector<int> adj[N], hadj[N], ladj[N];
bool isonline[N];
int finsz[N];
int online[N]; // Number of online friends (maintained ONLY for heavy nodes)

void solve() {
    int n, m, q;
    if (!(cin >> n >> m >> q)) return;

    // for testcases
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        hadj[i].clear();
        ladj[i].clear();
        isonline[i] = false;
        finsz[i] = 0;
        online[i] = 0;
    }


    // read online nodes
    int o; cin >> o;
    for (int i = 0; i < o; ++i) {
        int x; cin >> x;
        isonline[x] = true;
    }

    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        ++finsz[u];
        ++finsz[v];
    }

    // read offline query processing to pre-determine (heavy/light) nodes statically
    vector<pair<char, vector<int>>> qu(q);
    for (int i = 0; i < q; ++i) {
        char ch; cin >> ch;
        if (ch == 'O' || ch == 'F' || ch == 'C') {
            int u; cin >> u;
            qu[i] = {ch, {u}};
        } else if (ch == 'A' || ch == 'D') {
            int u, v; cin >> u >> v;
            qu[i] = {ch, {u, v}};
            if (ch == 'A') {
                ++finsz[u];
                ++finsz[v];
            }
        }
    }

    // distribute neighbors based on (maximum degree)
    for (int u = 1; u <= n; ++u) {
        for (auto v : adj[u]) {
            if (finsz[v] >= SQ) {
                hadj[u].emplace_back(v);
                online[v] += isonline[u];
            } else {
                ladj[u].emplace_back(v);
            }
        }
    }

    // for O(1) edge deletion
    auto erase_edge = [](vector<int>& vec, int target) {
        for (int i = 0; i < (int)vec.size(); ++i) {
            if (vec[i] == target) {
                swap(vec[i], vec.back());
                vec.pop_back();
                break;
            }
        }
    };


    for (int tk = 0; tk < q; ++tk) {
        char ch = qu[tk].first;

        if (ch == 'O') {
            int u = qu[tk].second[0];
            isonline[u] = true;
            for (auto v : hadj[u]) ++online[v];

        } else if (ch == 'F') {
            int u = qu[tk].second[0];
            isonline[u] = false;
            for (auto v : hadj[u]) --online[v];

        } else if (ch == 'A') {
            int u = qu[tk].second[0], v = qu[tk].second[1];

            if (finsz[v] >= SQ) {
                hadj[u].emplace_back(v);
                if (isonline[u]) ++online[v];
            } else {
                ladj[u].emplace_back(v);
            }

            if (finsz[u] >= SQ) {
                hadj[v].emplace_back(u);
                if (isonline[v]) ++online[u];
            } else {
                ladj[v].emplace_back(u);
            }

        } else if (ch == 'D') {
            int u = qu[tk].second[0], v = qu[tk].second[1];

            if (finsz[v] >= SQ) erase_edge(hadj[u], v);
            else erase_edge(ladj[u], v);

            if (finsz[u] >= SQ) erase_edge(hadj[v], u);
            else erase_edge(ladj[v], u);

            if (finsz[u] >= SQ) online[u] -= isonline[v];
            if (finsz[v] >= SQ) online[v] -= isonline[u];

        } else if (ch == 'C') {
            int u = qu[tk].second[0];

            if (finsz[u] >= SQ) {
                // Heavy node: Answer is precalculated
                cout << online[u] << '\n';
            } else {
                // Light node: Calculate on the fly
                int ans = 0;
                for (auto v : hadj[u]) if (isonline[v]) ++ans;
                for (auto v : ladj[u]) if (isonline[v]) ++ans;
                cout << ans << '\n';
            }
        }
    }
}
