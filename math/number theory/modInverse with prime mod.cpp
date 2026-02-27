/* (modInverse with prime mod)
* mod must be prime
 * a/b => ((a % mod) * (modinv(b)) % mod
 */
const int mod = 1e9 + 7;
ll fastpow(ll base, ll exp) {
  long long res = 1;
  base = base % mod;

  while (exp > 0) {
    if (exp % 2 == 1)
      res = (res * base) % mod;
    exp = exp >> 1;
    base = (base * base) % mod;
  }
  return res;
}
long long modinv(long long a) {
  return fastpow(a, mod - 2);
}