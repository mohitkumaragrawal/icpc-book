// phi(n) = # of integers in [1, n] that are relatively prime to n
// phi(p) = p - 1, where p is prime
// phi(p^k) = p^k - p^(k - 1) = p^k * (1 - 1 / p) for prime p;
void phi_1_to_n(int n) {
  vector<int> phi(n + 1);
  for (int i = 0; i <= n; i++) phi[i] = i;

  for (int i = 2; i <= n; i++) {
    if (phi[i] == i) {
      for (int j = i; j <= n; j += i) phi[j] -= phi[j] / i;
    }
  }
}
