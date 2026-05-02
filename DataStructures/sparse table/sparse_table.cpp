struct sparseTable {
  vector<vector<int>> spt;
  vector<int> lg;

  int merge(int a, int b) {
    return min(a, b);
  }

  sparseTable(const vector<int> &v) {
    int n = (int)v.size();
    lg.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i)
      lg[i] = 1 + lg[i / 2];

    int mxlg = lg[n];
    spt.assign(mxlg + 1, vector<int>(n));

    for (int j = 0; j < n; ++j) {
      spt[0][j] = v[j];
    }

    for (int i = 1; i <= mxlg; ++i) {
      for (int j = 0; j + (1 << i) <= n; ++j) {
        spt[i][j] = merge(spt[i - 1][j], spt[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  int get(int l, int r) { // 0-based
    int len = r - l + 1;
    int i = lg[len];
    return merge(spt[i][l], spt[i][r - (1 << i) + 1]);
  }
};