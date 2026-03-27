const int N = 2e5 + 5, M = 2e5 + 5; // (M * 2) if the graph is undirected.
int head[N], to[M], nxt[M], wt[M];
int eid;

void init(int n) {
  eid = 0;
  memset(head, -1, sizeof(head[0]) * (n + 1));
}

void addedge(int u, int v, int w) {
  to[eid] = v;
  nxt[eid] = head[u];
  wt[eid] = w;
  head[u] = eid++;
}

// traverse at neighbor of u
/*
 * for(int e = head[u]; e != -1; e = nxt[e]) {
 * int v = to[e], w = wt[e];
 * // process here
 * }
 */