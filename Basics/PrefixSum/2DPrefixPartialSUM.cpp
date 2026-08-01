const int N = 2005;
ll pref[N][N];

// 1-idx
void build_pref(int n, int m, const vector<vector<ll>>& a) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pref[i][j] = a[i][j]
                       + pref[i - 1][j]
                       + pref[i][j - 1]
                       - pref[i - 1][j - 1];
        }
    }
}

ll query(int x1, int y1, int x2, int y2) {
    return pref[x2][y2]
         - pref[x1 - 1][y2]
         - pref[x2][y1 - 1]
         + pref[x1 - 1][y1 - 1];
}

