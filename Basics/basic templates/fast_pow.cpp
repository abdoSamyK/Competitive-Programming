const int mod = 1e9 + 7;
ll fast_pow(ll base, ll exp) {
  ll res = 1;
  
  base %= mod;
  while (exp) {
    if (exp & 1)
      res = (res * base) % mod;

    base = (base * base) % mod;
    exp >>= 1;
  }
  return res;
}
