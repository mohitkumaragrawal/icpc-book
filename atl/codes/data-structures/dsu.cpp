struct DSU {
  vector<int> parent, siz;
  void init(int n) {
    parent.resize(n);
    siz.resize(n);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
      siz[i] = 1;
    }
  }
  int find(int x) {
    if (x == parent[x]) return x;
    return parent[x] = find(parent[x]);
  }
  void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (siz[x] < siz[y]) swap(x, y);
    parent[y] = x;
    siz[x] += siz[y];
  }
  int size(int x) { return siz[find(x)]; }
  bool same(int x, int y) { return find(x) == find(y); }
}
