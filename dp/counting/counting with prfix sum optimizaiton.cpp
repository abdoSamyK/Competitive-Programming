/***(AtCoder D-Leaping Tak) (Prefix Sum Optimization)
* given N children , and K candies
 * each child can receive candies from (0 to a[i])
 * Find the number of ways for them to share candies(with  no candies should be left over)
 *------------------------------------------------------------------------------------------------
 * dp[i][candies] = number of ways to share 'candies' among children i..n-1
 * Transition is a consecutive range sum -> use prefix sum to calculate it in o(1),
 */


const int mod = 1e9 + 7;
void cal() { //
  int n, k;cin >> n >> k;
  vector<int> v(n);
  for (int i = 0;i < n;++i) {
    cin >> v[i];
  }

  vector<vector<int>> dp(2, vector<int>(k + 1));
  // child i need only information about child (i - 1) it can be only 2 (child i and child (i - 1))
  dp[n&1][0] = 1;

  for (int i = n - 1;i >= 0;--i) {

    // pref[j] = sum of dp[i+1][0..j]
    vector<int> pref(k + 1);
    pref[0] = dp[(i + 1)&1][0];
    for (int j = 1;j <= k;++j) {
      pref[j] = pref[j - 1] + dp[(i + 1)&1][j];
      pref[j] = pref[j] % mod;
    }

    for (int j = 0;j <= k;++j) {
      int r = j, l = j - v[i] - 1;
      if (l >= 0) {
        dp[i&1][j] = pref[r] - pref[l];
      } else {
        dp[i&1][j] = pref[r];
      }
      dp[i&1][j] = (dp[i&1][j] + mod) % mod;

    }
  }
  cout << dp[0][k];
}
