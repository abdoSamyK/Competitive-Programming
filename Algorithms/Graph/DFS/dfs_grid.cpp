const int N = 1e3 + 3;
int n, m;
int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};
int vis[N][N];
void dfs_grid(int i, int j, vector<vector<char>> &g) {
  vis[i][j] = 1;
  auto isvalid = [&](int x, int y) {
    return (x >= 0 && y >= 0 && x < n && y < m && g[x][y] == '.' && !vis[x][y]);
  };
  for (int d = 0; d < 4; ++d) {
    int ni = i + di[d];
    int nj = j + dj[d];

    if (isvalid(ni, nj))
      dfs_grid(ni, nj, g);
  }
}