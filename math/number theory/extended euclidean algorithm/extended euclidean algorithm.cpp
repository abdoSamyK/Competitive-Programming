// a_i = b_{i-1}
// b_i = a_{i-1} % b_{i-1} = a_{i-1} - q_{i-1} * b_{i-1}
// where q_{i-1} = floor(a_{i-1} / b_{i-1})

// for (a_i, b_i) we have:
// a_i * x_i + b_i * y_i = g

// then for (a_{i-1}, b_{i-1}):
// x_{i-1} = y_i
// y_{i-1} = x_i - q_{i-1} * y_i
int eeaGCD(int a, int b, int& x, int& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1;
  int d = eeaGCD(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}