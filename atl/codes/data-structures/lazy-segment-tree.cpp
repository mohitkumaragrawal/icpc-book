template <typename node_type, typename tag_type> struct lazy_segtree {
  vector<node_type> tree;
  vector<tag_type> lazy;
  int n;
  template <typename Iter> void init(Iter first, Iter last, int nn = -1) {
    n = nn;
    if (n == -1)
      n = distance(first, last);
    tree.resize(4 * n);
    lazy.resize(4 * n);
    build_tree(0, 0, n - 1, first);
  }
  node_type query(int ql, int qr) { return query(0, 0, n - 1, ql, qr); }
  void update(int ql, int qr, tag_type const &val) {
    update(0, 0, n - 1, ql, qr, val);
  }

private:
  template <typename Iter> void build_tree(int id, int tl, int tr, Iter first) {
    if (tl == tr) {
      tree[id].init(tl, tr, *(first + tl));
      lazy[id].init(tl, tr);
      return;
    }
    int tm = (tl + tr) / 2;
    build_tree(2 * id + 1, tl, tm, first);
    build_tree(2 * id + 2, tm + 1, tr, first);
    tree[id] = node_type::merge(tree[2 * id + 1], tree[2 * id + 2]);
    lazy[id].init(tl, tr);
  }
  void push(int id, int tl, int tr) {
    if (tl != tr) {
      int tm = (tl + tr) / 2;
      tree[2 * id + 1].apply(tl, tm, lazy[id]);
      lazy[2 * id + 1].merge(lazy[id]);
      tree[2 * id + 2].apply(tm + 1, tr, lazy[id]);
      lazy[2 * id + 2].merge(lazy[id]);
    }
    lazy[id].reset();
  }
  node_type query(int id, int tl, int tr, int ql, int qr) {
    if (tl > qr || ql > tr)
      return node_type::phi();
    if (ql <= tl && tr <= qr)
      return tree[id];
    push(id, tl, tr);
    int tm = (tl + tr) / 2;
    return node_type::merge(query(2 * id + 1, tl, tm, ql, qr),
                            query(2 * id + 2, tm + 1, tr, ql, qr));
  }
  void update(int id, int tl, int tr, int ql, int qr, tag_type const &val) {
    if (tl > qr || ql > tr)
      return;
    if (ql <= tl && tr <= qr) {
      tree[id].apply(tl, tr, val);
      lazy[id].merge(val);
      return;
    }
    push(id, tl, tr);
    int tm = (tl + tr) / 2;
    update(2 * id + 1, tl, tm, ql, qr, val);
    update(2 * id + 2, tm + 1, tr, ql, qr, val);
    tree[id] = node_type::merge(tree[2 * id + 1], tree[2 * id + 2]);
  }
};
struct tag {
  ll inc;
  void reset() { inc = 0; }
  void merge(tag const &other) { inc += other.inc; }
  void init(int tl, int tr) {}
};
struct node {
  static node phi() { return {0LL}; }
  static node merge(node const &a, node const &b) { return {a.data + b.data}; }
  ll data;
  void apply(ll tl, ll tr, tag const &t) { data += (tr - tl + 1) * t.inc; }
  template <typename T> void init(ll tl, ll tr, T &ddata) {
    this->data = ddata;
  }
};
