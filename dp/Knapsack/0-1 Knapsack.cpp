/**
* find maximum possible sum of the values of items can get.
 *  ( n <= 100, mx_wt <= 1e5 ,
 *    w[i] <= mx_wt, v[i] <= 1e9 )
 *
 */
void knapsack() {
  int n, mx_wt;
  cin >> n >> mx_wt;
  vector<int> w(n), v(n);
  for (int i = 0;i < n;++i) cin >> w[i] >> v[i];
  vector<ll> dp(mx_wt + 1); // dp[w] = maximum value achieve with exact total weight w
  for (int i = 0;i < n;++i) {
    for (int wt = mx_wt; wt >= w[i]; --wt) {
      // if you can take the item many times (for (int wt = w[i]; wt <= mx_wt; ++wt)) -> Unbounded
      dp[wt] = max(dp[wt], dp[wt - w[i]] + v[i]);
    }
  }
  cout << dp[mx_wt];
}