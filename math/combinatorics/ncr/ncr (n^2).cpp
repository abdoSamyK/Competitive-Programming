/*(ncr with Pascal’s Triangle)
 * o(n^2)
 */
const int N = 1001;
long long nCr[N + 1][N + 1];

void precompute() {
  for (int n = 0; n <= N; n++) {
    for (int r = 0; r <= n; r++) {
      if (r == 0 || r == n)
        nCr[n][r] = 1;
      else
        nCr[n][r] = nCr[n-1][r] + nCr[n-1][r-1];
    }
  }
}