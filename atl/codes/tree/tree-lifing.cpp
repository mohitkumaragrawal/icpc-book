/*
 * Does all the binary lifting tasks in the same
 * time complexity but uses only O(n) memory;
 */
struct tree_lifting {
  vector<int> dep, jmp, fa;
  int n;
  void add_leaf(int cur, int par) {
    fa[cur] = par;
    dep[cur] = 1 + dep[par];
    if (dep[par] - dep[jmp[par]] == dep[jmp[par]] - dep[jmp[jmp[par]]]) {
      jmp[cur] = jmp[jmp[par]];
    } else {
      jmp[cur] = par;
    }
  }
  void dfs(int cur, int par, vector<vector<int>> &adj) {
    add_leaf(cur, par);
    for (int it : adj[cur]) {
      if (it == par)
        continue;
      dfs(it, cur, adj);
    }
  }
  void init(int nn) {
    dep.resize(nn), jmp.resize(nn), fa.resize(nn);
    this->n = nn;
  }
  int lift(int cur, int k) {
    int new_depth = max(dep[cur] - k, 0);
    while (dep[cur] > new_depth) {
      if (dep[jmp[cur]] >= new_depth)
        cur = jmp[cur];
      else
        cur = fa[cur];
    }
    return cur;
  }
  int lca(int u, int v) {
    if (dep[u] > dep[v])
      swap(u, v);
    v = lift(v, dep[v] - dep[u]);
    while (u != v) {
      if (jmp[v] != jmp[u]) {
        u = jmp[u];
        v = jmp[v];
      } else {
        u = fa[u];
        v = fa[v];
      }
    }
    return u;
  }
  int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
};
