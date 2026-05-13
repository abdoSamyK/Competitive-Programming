/**
* multiple Queries -> preprocessing
* * *: Count arrays where elements <= x and given Q queries.
* for each query count number of arrays witch sum of elements equal given n,
* * * optimization:
* `x` is constant --> `T` is constant.
* precompute binary powers of `T`: T^{2^0}, T^{2^1}, ..., T^{2^62}.
* for each query `n`, multiply the state vector by the precomputed T
* where the i-th bit of `n` is 1.
* * * Complexity:
* precomputation: O(X^3 * log(max_n))
* Per Query:      O(X^2 * log(N)) -> matrix * Vector multiplication is O(X^2)
*                                    because (S) is linear...
*/

void solve() {
  ll qn, x;
  cin >> qn >> x;

  // Precompute
  vector<matrix> T(63, matrix(x, row(x, 0)));

  // Build Base -> T^1 (T[0])
  for (int i = 0; i < x; ++i) {
    T[0][0][i] = 1;         // r0: dp[i] = dp[i-1] + ... + dp[i-x]
    if (i + 1 < x) {
      T[0][i + 1][i] = 1;   // shifting
    }
  }

  // T^(2^i)
  for (int i = 1; i < 63; ++i) {
    T[i] = mul(T[i - 1], T[i - 1]);
  }

  while (qn--) {
    ll n;
    cin >> n;

    matrix S(x, row(1, 0));
    S[0][0] = 1; // dp[0] = 1

    for (int i = 0; i < 63; ++i) {
      if ((n >> i) & 1) {
        S = mul(T[i], S);
      }
    }
    cout << S[0][0] << '\n';
  }
}