/**
* find :
 * sum(i^m) from i = 1 to n
 * n <= 1e18, m <= 100
 * * * :
 * for the new state .. ?
 * (i + 1)^m = sum[(mCj) * (i ^ j) * (1 ^ (m - j))];j (0  -> m) => polynomial expantion
 * ------
 * prefix sum + polynomial expansion.
 * (i+1)^k = sum(kCj * i^j) for j from 0 to k.
 * * * State Vector (Size m + 2):
 * S_i = {{Sum_{i}}, {i^0}, {i^1}, {i^2}, ..., {i^m}}
 * S_i = {{Sum_{i + 1}}, {(i + 1)^0}, {(i + 1)^1}, {(i + 1)^2}, ..., {(i + 1)^m}}
 * base case S_0 = { 0, 1, 0, 0, ..., 0 }  --> (Sum=0, 0^0=1, 0^1=0...)
 * * * T:
 * r0 (Sum): T[0][0] = 1. The rest of the row is mCj to add (i+1)^m.
 * rk (Powers): T[k][j] = (k-1)C(j-1) to generate (i+1)^(k-1).
 *
 *
 *
 * {
 *  if using at state [i] Sum_{i - 1}
 *  the first row at the T will be like that {{1, 0, 0, .. , 1}, ...}
 * T[0][0] = 1;
 * T[0][m + 1] = 1;     // add the current i^m
 *  because we calc it before and T = fast_pow(T, n + 1)
 * }
 */

vector<vector<ll>> nCr(int m) {
  vector<vector<ll>> C(m + 1, vector<ll>(m + 1, 0));
  for (int i = 0; i <= m; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
  }
  return C;
}

void solve() {
  ll n;
  int m;
  cin >> n >> m;

  if (n == 0) {
    cout << 0 << '\n';
    return;
  }
  vector<vector<ll>> C = nCr(m);

  // S_0 = { Sum_0, 0^0, 0^1, ..., 0^m } -> { 0, 1, 0, ..., 0 }
  matrix S(m + 2, row(1, 0));
  S[1][0] = 1; // 0^0 is treated as 1 to carry the constant term

  matrix T(m + 2, row(m + 2, 0));

  // Row 0: Accumulate the sum -> sum_{i+1} = sum_i + (i+1)^m
  T[0][0] = 1; // Carry over previous sum
  for (int j = 0; j <= m; ++j) {
    T[0][j + 1] = C[m][j]; // Add mCj * i^j
  }

  // r1 to m+1: generate (i+1)^k for k from 0 to m
  for (int k = 0; k <= m; ++k) {
    for (int j = 0; j <= k; ++j) {
      T[k + 1][j + 1] = C[k][j]; // (i+1)^k = sum( kCj * i^j )
    }
  }

  T = fas_pow(T, n);
  S = mul(T, S);

  cout << S[0][0] << '\n';
}