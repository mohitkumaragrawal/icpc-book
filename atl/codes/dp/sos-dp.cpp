const ll MLOG = 20;
const ll MAXN = 1 << MLOG;
ll dp[MAXN];

void forward1() {  // adding element to all its super set
  for (ll bit = 0; bit < MLOG; ++bit) {
    for (ll i = 0; i < MAXN; ++i) {
      if (i & (1 << bit)) {
        dp[i] += dp[i ^ (1 << bit)];
      }
    }
  }
}

void backward1() {  // add a[i] to a[j] if j&i = i
  for (ll bit = 0; bit < MLOG; ++bit) {
    for (ll i = MAXN - 1; i >= 0; --i) {
      if (i & (1 << bit)) {
        dp[i] -= dp[i ^ (1 << bit)];
      }
    }
  }
}
void forward2() {  // add elements to its subsets
  for (ll bit = 0; bit < MLOG; ++bit) {
    for (ll i = MAXN - 1; i >= 0; --i) {
      if (i & (1 << bit)) {
        dp[i ^ (1 << bit)] += dp[i];
      }
    }
  }
}
void backward2() {
  for (ll bit = 0; bit < MLOG; ++bit) {
    for (ll i = 0; i < MAXN; ++i) {
      if (i & (1 << bit)) {
        dp[i ^ (1 << bit)] -= dp[i];
      }
    }
  }
}