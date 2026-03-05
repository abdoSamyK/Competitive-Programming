const int N = 2e5 + 2;
const ll mod = 1e9 + 7;
ll fac[N + 5], invfac[N + 5];

ll fastpow(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1) res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}
void factorial() {
  fac[0] = 1;
  for (int i = 1; i < N; i++) { fac[i] = fac[i - 1] * i % mod; }
}
void inversefact() {
  invfac[N - 1] = fastpow(fac[N - 1], mod - 2);
  for (int i = N - 1; i >= 1; i--) {
    invfac[i - 1] = invfac[i] * i % mod;
  }
}
void initncr() {
  // make it at main
  factorial();
  inversefact();
}
ll nCr(int n, int r) {
  if (r > n || r < 0) return 0;
  return fac[n] * invfac[r] % mod * invfac[n - r] % mod;
}
