/**
* prefix sum,,,
* * *: count number of arrays of any length where each element v[i] <= x,
* such that the sum of all elements <= n.
* * * form (sum == n):
* ans = dp[1] + dp[2] + dp[3] + .... + dp[n]
* dp[i] = dp[i-1] + dp[i-2] + ... + dp[i-x]
* * *
* pref[i] = pref[i-1] + dp[i]
* final answer is pref[n] - dp[0] (subtract 1 to remove the empty array).
* * * state :
* S_i     = { pref[i-1], dp[i],   dp[i-1], ..., dp[i-x+1] }
* S_{i+1} = { pref[i],   dp[i+1], dp[i],   ..., dp[i-x+2] }
* * * transition matrix (T) (for x = 3):
* [ 1  1  0  0 ]   [ pref[i-1] ]     [ pref[i] ]    (pref[i] = pref[i-1] + dp[i])
* [ 0  1  1  1 ]   [ dp[i]     ]     [ dp[i+1] ]    (dp[i+1] = dp[i] + dp[i-1] + dp[i-2])
* [ 0  1  0  0 ] * [ dp[i-1]   ]  =  [ dp[i]   ]    (shift)
* [ 0  0  1  0 ]   [ dp[i-2]   ]     [ dp[i-1] ]    (shift)
*
*
* O(x^3 (log n))$
*/

void solve() {
  ll n, x;
  cin >> n >> x;

  // base case(i = 0)
  // S_0 = { pref[-1], dp[0], dp[-1], ... } -> { 0, 1, 0, 0... }
  matrix S(x + 1, row(1, 0));
  S[1][0] = 1;

  // transition T :
  matrix T(x + 1, row(x + 1, 0));

  // r0 : (pref[i] = pref[i-1] + dp[i])
  T[0][0] = 1;
  T[0][1] = 1;

  // r1 : (dp[i+1] = dp[i] + ... + dp[i-x+1])
  for (int i = 1; i <= x; ++i) {
    T[1][i] = 1;
  }

  // shifting
  for (int i = 2; i <= x; ++i) {
    T[i][i - 1] = 1;
  }

  T = fas_pow(T, n + 1);
  S = mul(T, S);

  ll ans = (S[0][0] - 1 + mod) % mod;

  cout << ans << '\n';
}