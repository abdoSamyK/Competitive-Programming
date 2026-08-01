/*
 * topological Sort (Kahn's algorithm)
 * false if a cycle exist
 */

const int N = 1e5 + 5;
int n;
vector<int> adj[N];
vector<int> topo;

bool topo_sort() {
    vector<int> indegree(n + 1, 0);
    for (int u = 1; u <= n; u++)
        for (int v : adj[u])
            indegree[v]++;

    queue<int> q;
    /**
     *(to find lexicographically smallest topological order)
     * just use : priority_queue<int, vector<int>, greater<int>> q;
     * instead of queue<int> q;
     */
    for (int i = 1; i <= n; i++)
        if (indegree[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        topo.push_back(u);

        for (int v : adj[u])
            if (--indegree[v] == 0)
                q.push(v);
    }

    return topo.size() == n;
}
