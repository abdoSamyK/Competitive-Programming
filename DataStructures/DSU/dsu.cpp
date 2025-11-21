const int N = 1e5 + 5;
int parent[N], sz[N];

// make_set(v) -> Initializes element v as a new set
void make_set(int v) {
    parent[v] = v;
    sz[v] = 1;
}

// find_set(v) -> Returns the representative (root) of the set containing v
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]); // Path compression
}

// union_sets(a, b) -> Merges the sets containing a and b
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b); // Merge smaller tree into larger tree
        parent[b] = a;
        sz[a] += sz[b];
    }
}