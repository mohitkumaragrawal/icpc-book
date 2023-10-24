const ll MOD = 1e9 + 7;
ll binexp(ll a, ll b, ll p = MOD) {
  if (b < 0)
    return 0;
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      b--, res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

inline ll modinv(ll x, ll p = MOD) { return binexp(x, p - 2, p); }
template <ll mod> struct MODINT_ {
  ll value;
  MODINT_() = default;
  MODINT_(ll x) : value(x % mod) {}
  MODINT_(const MODINT_ &m) : value(m.value % mod) {}
  MODINT_ &operator=(const MODINT_ &m) {
    value = m.value;
    return *this;
  }
  ll inverse_value() const { return modinv(value, mod); }
  MODINT_ &operator+=(const MODINT_ &m) {
    value = (value + m.value) % mod;
    return *this;
  }
  MODINT_ &operator-=(const MODINT_ &m) {
    value = (mod + value - m.value) % mod;
    return *this;
  }
  MODINT_ &operator*=(const MODINT_ &m) {
    value = (value * m.value) % mod;
    return *this;
  }
  MODINT_ &operator/=(const MODINT_ &m) {
    value = (value * m.inverse_value()) % mod;
    return *this;
  }
  MODINT_ &operator++() {
    value++;
    value %= mod;
    return *this;
  }
  MODINT_ &operator--() {
    value--;
    value %= mod;
    return *this;
  }
  MODINT_ operator*(const MODINT_ &b) { return MODINT_(value * b.value); }
  MODINT_ operator*(ll b) { return MODINT_(value * b); }
  MODINT_ operator-(const MODINT_ &b) { return MODINT_(mod + value - b.value); }
  MODINT_ operator-(ll b) { return MODINT_(mod + value - b); }
  MODINT_ operator+(const MODINT_ &b) { return MODINT_(value + b.value); }
  MODINT_ operator+(ll b) { return MODINT_(value + b); }
  MODINT_ operator/(const MODINT_ &b) {
    return MODINT_(value * modinv(b.value, mod));
  }
  MODINT_ operator/(ll b) { return MODINT_(value * modinv(b, mod)); }
};
template <ll mod> ostream &operator<<(ostream &out, const MODINT_<mod> &m) {
  out << m.value % mod;
  return out;
}
template <ll mod> istream &operator>>(istream &in, MODINT_<mod> &m) {
  ll x;
  in >> x;
  m.value = (x % mod);
  return in;
}
using MODINT = MODINT_<MOD>;
vector<MODINT> factorial;
void init_factorial() {
  factorial.resize(1000005);
  factorial[0] = factorial[1] = 1;
  for (ll i = 2; i < 1000005; ++i) {
    factorial[i] = (factorial[i - 1] * i);
  }
}
inline MODINT choose(const MODINT &a, const MODINT &b) {
  if (a.value < b.value)
    return 0;
  return factorial[a.value] /
         (factorial[b.value] * factorial[(a.value - b.value)]);
}
