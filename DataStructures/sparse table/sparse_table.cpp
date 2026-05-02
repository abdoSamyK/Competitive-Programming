struct sparseTable {
  vector<vector<int>> spt;
  vector<int> lg;

  int merge(int a, int b) {
    return min(a, b);
  }

  sparseTable(vector<int> &v) {
    int n = (int)v.size();
    lg.assign(n + 1, 0);
    for (int i = 2;i <= n;++i) {
      lg[i] = 1 + lg[i/2];
    }
    spt.assign(lg[n] + 1, vector<int>(n));
    spt[0] = v;
    for (int i = 1; i <= lg[n]; ++i) {
      int l = (1 << i);
      for (int j = 0; j + l <= n; ++j) {
        spt[i][j] = merge(spt[i - 1][j], spt[i - 1][j + (l >> 1)]);
      }
    }
  }
  int get(int l, int r) {
    int len = r - l + 1;
    int j = lg[len];
    return merge(spt[j][l], spt[j][r - (1 << j) + 1]);
  }
};