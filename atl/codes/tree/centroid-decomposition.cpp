#include <bits/stdc++.h>

struct lca_lift {
  const int lg = 24;
  int n;
  vector<int> depth;
  vector<vector<int> > edges;
  vector<vector<int> > lift;

  void init(int sz) {
    n = sz;
    depth = vector<int>(n);
    edges = vector<vector<int> >(n, vector<int>());
    lift = vector<vector<int> >(n, vector<int>(lg, -1));
  }

  void edge(int a, int b) {
    edges[a].push_back(b);
    edges[b].push_back(a);
  }

  void attach(int node_to_attach, int node_to_attach_to) {
    int a = node_to_attach, b = node_to_attach_to;
    edge(a, b);

    lift[a][0] = b;

    for (int i = 1; i < lg; i++) {
      if (lift[a][i - 1] == -1)
        lift[a][i] = -1;
      else
        lift[a][i] = lift[lift[a][i - 1]][i - 1];
    }

    depth[a] = depth[b] + 1;
  }

  void init_lift(int v = 0) {
    depth[v] = 0;
    dfs(v, -1);
  }

  void dfs(int v, int par) {
    lift[v][0] = par;

    for (int i = 1; i < lg; i++) {
      if (lift[v][i - 1] == -1)
        lift[v][i] = -1;
      else
        lift[v][i] = lift[lift[v][i - 1]][i - 1];
    }

    for (int x : edges[v]) {
      if (x != par) {
        depth[x] = depth[v] + 1;
        dfs(x, v);
      }
    }
  }

  int get(int v, int k) {
    for (int i = lg - 1; i >= 0; i--) {
      if (v == -1) return v;
      if ((1 << i) <= k) {
        v = lift[v][i];
        k -= (1 << i);
      }
    }
    return v;
  }

  int get_lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int d = depth[a] - depth[b];
    int v = get(a, d);
    if (v == b) {
      return v;
    } else {
      for (int i = lg - 1; i >= 0; i--) {
        if (lift[v][i] != lift[b][i]) {
          v = lift[v][i];
          b = lift[b][i];
        }
      }
      return lift[b][0];
    }
  }

  int get_dist(int a, int b) {
    int v = get_lca(a, b);
    return depth[a] + depth[b] - 2 * depth[v];
  }
};

struct centroid {
  vector<vector<int> > edges;
  vector<bool> vis;
  vector<int> par;
  vector<int> sz;
  int n;

  void init(int s) {
    n = s;
    edges = vector<vector<int> >(n, vector<int>());
    vis = vector<bool>(n, 0);
    par = vector<int>(n);
    sz = vector<int>(n);
  }

  void edge(int a, int b) {
    edges[a].pb(b);
    edges[b].pb(a);
  }

  int find_size(int v, int p = -1) {
    if (vis[v]) return 0;
    sz[v] = 1;

    for (int x : edges[v]) {
      if (x != p) {
        sz[v] += find_size(x, v);
      }
    }

    return sz[v];
  }

  int find_centroid(int v, int p, int n) {
    for (int x : edges[v]) {
      if (x != p) {
        if (!vis[x] && sz[x] > n / 2) {
          return find_centroid(x, v, n);
        }
      }
    }

    return v;
  }

  void init_centroid(int v = 0, int p = -1) {
    find_size(v);

    int c = find_centroid(v, -1, sz[v]);
    vis[c] = true;
    par[c] = p;

    for (int x : edges[c]) {
      if (!vis[x]) {
        init_centroid(x, c);
      }
    }
  }
};

ll n, m, k, q, l, r, x, y, z;
ll a[1000005];
ll b[1000005];
ll c[1000005];
string s, t;
ll ans = 0;

lca_lift lca;
centroid ct;
int best[100005];

void update(int v) {
  best[v] = 0;

  int u = v;
  while (ct.par[u] != -1) {
    u = ct.par[u];
    best[u] = min(best[u], lca.get_dist(u, v));
  }
}

int query(int v) {
  int ans = best[v];

  int u = v;
  while (ct.par[u] != -1) {
    u = ct.par[u];
    ans = min(ans, best[u] + lca.get_dist(u, v));
  }
  return ans;
}

void solve(int tc = 0) {
  cin >> n >> q;

  lca.init(n);
  ct.init(n);

  f0r(i, n) best[i] = 2e5;

  f0r(i, n - 1) {
    cin >> x >> y;
    --x;
    --y;
    lca.edge(x, y);
    ct.edge(x, y);
  }

  lca.init_lift();
  ct.init_centroid();

  update(0);  // include this b/c node 1 is initially red

  f0r(i, q) {
    int t;
    cin >> t >> x;
    --x;

    if (t == 1)
      update(x);
    else
      cout << query(x) << '\n';
  }
}

int main() {
#ifdef galen_colin_local
  auto begin = std::chrono::high_resolution_clock::now();
#endif

  send help

#ifndef galen_colin_local
  // usaco("cowland");
#endif

      // usaco("cowland");

      int tc = 1;
  // cin >> tc;
  for (int t = 0; t < tc; t++) solve(t);

#ifdef galen_colin_local
  auto end = std::chrono::high_resolution_clock::now();
  cout << setprecision(4) << fixed;
  // cout << "Execution time: " <<
  // std::chrono::duration_cast<std::chrono::duration<double>>(end -
  // begin).count() << " seconds" << endl;
#endif
}