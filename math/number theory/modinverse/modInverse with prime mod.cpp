/*
 * If m is prime and gcd(a, m) = 1, then by Fermat's Little Theorem:
 *     a^(m-1) ≡ 1 (mod m)
 * Multiplying both sides by a^(-1):
 *     a^(m-2) * a ≡ 1 (mod m)
 * Therefore, the modular inverse of a modulo m is:
 *     a^(-1) ≡ a^(m-2) (mod m)
*/
ll power(ll base, ll exp, ll mod) {
  ll res = 1;
  base = base % mod;

  while (exp > 0) {
    if (exp % 2 == 1)
      res = (res * base) % mod;
    exp = exp >> 1;
    base = (base * base) % mod;
  }
  return res;
}
ll modInverseFermat(ll a, ll m) {
  // 'm' ust be a prime
  return power(a, m - 2, m);
}