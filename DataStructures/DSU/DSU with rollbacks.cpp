const int N = 2e5 + 5;
int parent[N], sz[N];
int components;

vector<array<int, 4>> roll_st;

void init_dsu(int n) {
  components = n;
  roll_st.clear();
  for (int i = 1; i <= n; i++) {
    parent[i] = i;
    sz[i] = 1;
  }
}

int find_set(int v) {
  if (v == parent[v])
    return v;
  return find_set(parent[v]);
}

void union_sets(int u, int v) {
  int a = find_set(u);
  int b = find_set(v);

  if (a != b) {
    if (sz[a] < sz[b]) swap(a, b);

    roll_st.push_back({a, sz[a], b, parent[b]});

    parent[b] = a;
    sz[a] += sz[b];
    components--;
  } else {
    roll_st.push_back({-1, -1, -1, -1});
  }
}

void rollback() {
  if (roll_st.empty()) return;

  auto arr = roll_st.back();
  roll_st.pop_back();
  if (arr[0] == -1) return;

  parent[arr[2]] = arr[3];
  sz[arr[0]] = arr[1];
  components++;
}