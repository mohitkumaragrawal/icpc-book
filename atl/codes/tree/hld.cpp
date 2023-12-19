#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <int SZ, bool VALS_IN_EDGES>
struct HLD {
  int N;
  vector<int> adj[SZ];
  int par[SZ], root[SZ], depth[SZ], sz[SZ], ti;
  int pos[SZ];

  vector<int> rpos;  // not used but could be useful;

  void ae(int x, int y) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  void dfsSz(int x) {
    sz[x] = 1;
    for (auto &y : adj[x]) {
      par[y] = x;
      depth[y] = depth[x] + 1;
      adj[y].erase(find(adj[y].begin(), adj[y].end(), x));
      dfsSz(y);
      sz[x] += sz[y];
      if (sz[y] > sz[adj[x][0]]) swap(y, adj[x][0]);
    }
  }

  void dfsHld(int x) {
    pos[x] = ti++;
    rpos.push_back(x);

    for (auto &y : adj[x]) {
      root[y] = (y == adj[x][0] ? root[x] : y);
      dfsHld(y);
    }
  }

  void init(int _N, int R = 0) {
    N = _N;
    par[R] = depth[R] = ti = 0;
    dfsSz(R);
    root[R] = R;
    dfsHld(R);
  }

  int lca(int x, int y) {
    for (; root[x] != root[y]; y = par[root[y]]) {
      if (depth[root[x]] > depth[root[y]]) swap(x, y);
    }
    return depth[x] < depth[y] ? x : y;
  }

  int dist(int x, int y) { return depth[x] + depth[y] - 2 * depth[lca(x, y)]; }

  template <class BinaryOp>
  void processPath(int x, int y, BinaryOp op) {
    for (; root[x] != root[y]; y = par[root[y]]) {
      if (depth[root[x]] > depth[root[y]]) swap(x, y);
      op(pos[root[y]], pos[y]);
    }
    if (depth[x] > depth[y]) swap(x, y);
    op(pos[x] + VALS_IN_EDGES, pos[y]);
  }

  void modifyPath(int x, int y, int v) {
    processPath(x, y, [this, &v](int l, int r) {
      // modify range [l, r]
    });
  }

  ll queryPath(int x, int y) {
    ll res = 0;
    processPath(x, y, [this, &res](int l, int r) {
      // query range [l, r]
    });
    return res;
  }

  void modifySubtree(int x, int v) {
    // update range
    // [ pos[x] + VALS_IN_EDGES, pos[x] + sz[x] - 1 ]
  }
};
