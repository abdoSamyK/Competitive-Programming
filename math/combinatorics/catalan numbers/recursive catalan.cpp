/*(Catalan with recursive way)
 * O(n^2)
 */
const int mod = 1e9 + 7;
const int N = 2005;
ll cat[N + 1];
ll catalan(int n) {
  if (n <= 1) {
      return 1;
  }
  if (cat[n] != -1) return cat[n];

  ll res = 0;
  for (int i = 0; i < n; i++) {
    res = (res + catalan(i) * catalan(n - 1 - i) % mod) % mod;
  }
  return cat[n] = res;
}

void initcat(int n) {
  memset(cat, -1, sizeof(cat));
  cat[0] = cat[1] = 1;
  catalan(n);
}