const int mod = 1e9 + 7;
using row  = vector<ll>;
using matrix = vector<row>;

matrix mul(const matrix &a, const matrix &b) {
  int ra = a.size(), ca = a[0].size(), cb = b[0].size();
  matrix res(ra, row(cb, 0));
  for (int i = 0; i < ra; ++i) {
    for (int o = 0; o < ca; ++o) {
      for (int j = 0; j < cb; ++j) {
        res[i][j] = (res[i][j] + a[i][o] * b[o][j] % mod) % mod;
      }
    }
  }
  return res;
}
matrix fas_pow(matrix a, ll p) {
  int n = (int)a.size();
  matrix res(n, row(n, 0)); // I matrix
  for (int i = 0;i < n;++i) {
    res[i][i] = 1;
  }
  while (p) {
    if (p & 1) res = mul(res, a);
    a = mul(a, a);
    p >>= 1;
  }
  return res;
}