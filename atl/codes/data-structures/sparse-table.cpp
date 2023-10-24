struct min_op {
  ll operator()(ll a, ll b) { return min(a, b); }
};
struct max_op {
  ll operator()(ll a, ll b) { return max(a, b); }
};
struct gcd_op {
  ll operator()(ll a, ll b) { return __gcd(a, b); }
};
template <typename OperationT> struct sparse_table {
  vector<vector<ll>> m;
  OperationT op;
  template <typename Itr> void init(Itr begin, Itr end) {
    ll sz = end - begin;
    ll lg = 63 - __builtin_clzll(sz);
    m.assign(sz, vector<ll>(lg + 1));
    for (ll j = 0; j <= lg; ++j) {
      ll len = (1 << j);
      for (ll i = 0; i + len - 1 < sz; ++i) {
        if (len == 1) {
          m[i][j] = *(begin + i);
        } else {
          m[i][j] = op(m[i][j - 1], m[i + (1 << (j - 1))][j - 1]);
        }
      }
    }
  }
  ll query(ll L, ll R) {
    ll j = 63 - __builtin_clzll((R - L + 1));
    return op(m[L][j], m[R + 1 - (1 << j)][j]);
  }
};
