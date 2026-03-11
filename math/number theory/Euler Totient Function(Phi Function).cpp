/*
 * count the number from [1, n] that are coprime to n.
 */
const int N = 1e5 + 5;
int phi[N];
void prephi() {
  for (int i = 1; i < N; i++) phi[i] = i;
  for (int i = 2; i < N; i++) {
    if (phi[i] == i) {
      for (int j = i; j < N; j += i) phi[j] -= phi[j] / i;
    }
  }
}