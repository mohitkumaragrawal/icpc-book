const ll MOD = 1e9 + 7;
ll binexp(ll a, ll b, ll p = MOD) {
  if (b < 0) return 0;
  ll res = 1;
  while (b > 0) {
    if (b & 1) b--, res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

inline ll modinv(ll x, ll p = MOD) { return binexp(x, p - 2, p); }
template <ll mod>
struct mi_ {
  ll value;
  mi_() = default;
  mi_(ll x) : value(x % mod) {}
  mi_(const mi_ &m) : value(m.value % mod) {}
  mi_ &operator=(const mi_ &m) {
    value = m.value;
    return *this;
  }
  ll inverse_value() const { return modinv(value, mod); }
  mi_ &operator+=(const mi_ &m) {
    value = (value + m.value) % mod;
    return *this;
  }
  mi_ &operator-=(const mi_ &m) {
    value = (mod + value - m.value) % mod;
    return *this;
  }
  mi_ &operator*=(const mi_ &m) {
    value = (value * m.value) % mod;
    return *this;
  }
  mi_ &operator/=(const mi_ &m) {
    value = (value * m.inverse_value()) % mod;
    return *this;
  }
  mi_ &operator++() {
    value++;
    value %= mod;
    return *this;
  }
  mi_ &operator--() {
    value--;
    value %= mod;
    return *this;
  }
  mi_ operator*(const mi_ &b) { return mi_(value * b.value); }
  mi_ operator*(ll b) { return mi_(value * b); }
  mi_ operator-(const mi_ &b) { return mi_(mod + value - b.value); }
  mi_ operator-(ll b) { return mi_(mod + value - b); }
  mi_ operator+(const mi_ &b) { return mi_(value + b.value); }
  mi_ operator+(ll b) { return mi_(value + b); }
  mi_ operator/(const mi_ &b) { return mi_(value * modinv(b.value, mod)); }
  mi_ operator/(ll b) { return mi_(value * modinv(b, mod)); }
};
template <ll mod>
ostream &operator<<(ostream &out, const mi_<mod> &m) {
  out << m.value % mod;
  return out;
}
template <ll mod>
istream &operator>>(istream &in, mi_<mod> &m) {
  ll x;
  in >> x;
  m.value = (x % mod);
  return in;
}
using mi = mi_<MOD>;
vector<mi> factorial;
void init_factorial() {
  factorial.resize(1000005);
  factorial[0] = factorial[1] = 1;
  for (ll i = 2; i < 1000005; ++i) {
    factorial[i] = (factorial[i - 1] * i);
  }
}
inline mi choose(const mi &a, const mi &b) {
  if (a.value < b.value) return 0;
  return factorial[a.value] /
         (factorial[b.value] * factorial[(a.value - b.value)]);
}
