struct euler_tour {
  vector<ll> in, out;
  ll timer = 0;
  void init(vector<vector<ll>> &adj) {
    ll n = adj.size();
    in.resize(n);
    out.resize(n);
    function<void(ll, ll)> dfs = [&](ll u, ll p) {
      in[u] = timer++;
      for (ll v : adj[u]) {
        if (v != p)
          dfs(v, u);
      }
      out[u] = timer++;
    };
    dfs(0, 0);
  }
  bool is_ancestor(ll u, ll v) { return in[u] <= in[v] && out[u] >= out[v]; }
};
