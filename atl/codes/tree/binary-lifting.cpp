struct binary_lift {
  vector<vector<ll>> children;
  vector<ll> depth;
  const ll LOG = 18;
  void init(vector<vector<ll>> &adj) {
    ll n = adj.size();
    depth.resize(n);
    children.assign(n, vector<ll>(LOG + 1));
    function<void(ll, ll, ll)> dfs = [&](ll u, ll p, ll d) {
      depth[u] = d;
      children[u][0] = p;
      for (ll i = 1; i <= LOG; ++i) {
        children[u][i] = children[children[u][i - 1]][i - 1];
      }
      for (ll v : adj[u]) {
        if (v != p)
          dfs(v, u, d + 1);
      }
    };
    dfs(0, 0, 0);
  }
  ll lift_node(ll n, ll d) {
    for (ll i = LOG; i >= 0; --i) {
      if (d & (1 << i))
        n = children[n][i];
    }
    return n;
  }
  ll lca(ll u, ll v) {
    if (depth[u] < depth[v])
      swap(u, v);
    u = lift_node(u, depth[u] - depth[v]);
    if (u == v)
      return u;
    for (ll i = LOG; i >= 0; --i) {
      if (children[u][i] != children[v][i]) {
        u = children[u][i];
        v = children[v][i];
      }
    }
    return children[u][0];
  }
  ll dist(ll u, ll v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }
};
