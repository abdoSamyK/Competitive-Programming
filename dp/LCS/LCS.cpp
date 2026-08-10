// Longest Common Subsequence
void LCS() { //
  int n, m;cin >> n >> m;
  vector<int> a(n + 1), b(m + 1);
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= m; ++i) cin >> b[i];

  vector<vector<int>> dp(n + 1, vector<int>(m + 1));
  for (int i = 1;i <= n;++i) {
    for (int j = 1;j <= m;++j) {
      if (a[i] == b[j]) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
      }
      dp[i][j] = max({dp[i][j], dp[i - 1][j], dp[i][j - 1]});
    }
  }

  int i = n, j = m;
  vector<int> ans;
  while (i >= 1 && j >= 1) {
    if (a[i] == b[j] && dp[i][j] == dp[i - 1][j - 1] + 1) {
      ans.emplace_back(a[i]);
      --i;--j;
    } else if (dp[i][j] == dp[i][j - 1]) {
      --j;
    } else {
      --i;
    }
  }
  reverse(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (auto it : ans) cout << it << ' ';
}