/*
 * by using(Extended Euclidean Algorithm):
 *     a*x + b*y = g, where g = gcd(a, b)
 *
 * taking both sides modulo b:
 *     a*x ≡ g (mod b)
 * since b*y ≡ 0 (mod b)
 *
 * If g = 1, then:
 *     a*x ≡ 1 (mod b)
 *
 * so x is the mod inverse of a modulo b:
 *     x = a^(-1) (mod b)
 * ->exists only when gcd(a, b) = 1
*/
int eGCD(int a, int b, int &x, int &y) {
  // Base Case
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  int x1, y1;
  int gcd = eGCD(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return gcd;
}

int modInverseEGCD(int a, int m) {
  int x, y;
  int gcd = eGCD(a, m, x, y);

  if (gcd != 1) {
    return -1;
  } else {
    return (x % m + m) % m; // avoid when x < 0 (return x)
  }
}