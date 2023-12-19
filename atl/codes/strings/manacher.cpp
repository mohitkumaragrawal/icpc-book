struct manacher {
  vll p;

  void run_manacher(string s) {
    ll n = s.size();
    p.assign(n, 1);
    ll l = 1, r = 1;

    for (ll i = 1; i < n; i++) {
      p[i] = max(0ll, min(r - i, p[l + r - i]));
      while (i + p[i] < n && i - p[i] >= 0 && s[i + p[i]] == s[i - p[i]]) {
        p[i]++;
      }
      if (i + p[i] > r) {
        l = i - p[i];
        r = i + p[i];
      }
    }
  }

  void build(string s) {
    string t;
    for (auto v : s) {
      t += string("#") + v;
    }
    run_manacher(t + "#");
  }

  ll getLongest(ll cen, bool odd) {
    ll pos = 2 * cen + 1 + (!odd);
    return p[pos] - 1;
  }

  bool checkPalin(ll l, ll r) {
    if ((r - l + 1) <= getLongest((l + r) / 2, (l % 2 == r % 2))) {
      return true;
    }
    return false;
  }
};