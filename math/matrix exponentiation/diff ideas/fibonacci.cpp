/**(Fibonacci[n], (n <= 1e18)
* f[i] = f[i - 1] + f[i - 2],,,
* state(S_i) : {{i}, {{i - 1}}
* new state(S_(i + 1)) : {{i + 1}, {i}}
* transition T : {{1, 1}, {1, 0}}
* base case : fib[0] = 0, fib[1] = 1
*/
void solve() {
  ll n;cin >> n;
  matrix S = {{1},
{0}};

  matrix T = {{1, 1},
{1, 0}};

  T = fas_pow(T, n);
  S = mul(T, S);
  cout << S[1][0];
}
