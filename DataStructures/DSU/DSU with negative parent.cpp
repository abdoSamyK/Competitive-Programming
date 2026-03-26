const int N = 1e5 + 5;
int parent[N];
int components;

void init(int n) { // make it for each testcase
  fill(parent, parent + n + 1, -1);
  components = n;
}

int find_set(int v) {
  if (parent[v] < 0) return v;
  return parent[v] = find_set(parent[v]); // path compression
}

bool union_sets(int a, int b) {
  a = find_set(a);
  b = find_set(b);

  if (a == b) return false;

  if (-parent[a] < -parent[b]) swap(a, b); // union by size

  parent[a] += parent[b]; // (-) + (-)
  parent[b] = a;
  components--;
  return true;
}
