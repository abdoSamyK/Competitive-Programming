/*(catalan with iterative way)
 * O(n^2)
 */
const int mod = 1e9 + 7;
const int N = 2005;
ll cat[N + 1];
void catalan_iterative(int n) {
  cat[0] = cat[1] = 1;

  for (int i = 2; i <= n; i++) {
    cat[i] = 0;
    for (int j = 0; j < i; j++) {
      cat[i] = (cat[i] + cat[j] * cat[i - 1 - j] % mod) % mod;
    }
  }
}