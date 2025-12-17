#define ll long long
// 2D Partial Sums (Difference Array) & Prefix Sums(can make it use the same vector)

// 2D Partial Sum => o(1)
void add(vector<vector<ll>>& a, int x1, int y1, int x2, int y2, int val) {
    a[x1][y1] += val;
    a[x1][y2 + 1] -= val;
    a[x2 + 1][y1] -= val;
    a[x2 + 1][y2 + 1] += val;
}

// 2D Prefix Sum => o(n * m)
vector<vector<ll>> build(const vector<vector<ll>>& a, int n, int m) {
    vector<vector<ll>> pref(n + 2, vector<ll>(m + 2, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + a[i][j];
        }
    }
    return pref;
}
/*
Q sum of sub-rectangle (x1, y1) -> (x2, y2):
ll res = pref[x2][y2]
       - pref[x1 - 1][y2]
       - pref[x2][y1 - 1]
       + pref[x1 - 1][y1 - 1];
*/