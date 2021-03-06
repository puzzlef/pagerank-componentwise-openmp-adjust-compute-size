#pragma once
#include <vector>
#include "vertices.hxx"

using std::vector;




// DFS
// ---
// Traverses nodes in depth-first manner, listing on entry.

template <class G, class F>
void dfsDoLoop(vector<bool>& vis, const G& x, int u, F fn) {
  if (vis[u]) return;  // dont visit if done already!
  vis[u] = true; fn(u);
  for (int v : x.edges(u))
    if (!vis[v]) dfsDoLoop(vis, x, v, fn);
}

template <class G, class F>
void dfsDo(const G& x, int u, F fn) {
  auto vis = createContainer(x, bool());
  dfsDoLoop(vis, x, u, fn);
}


template <class G>
void dfsLoop(vector<int>& a, vector<bool>& vis, const G& x, int u) {
  dfsDoLoop(vis, x, u, [&](int u) { a.push_back(u); });
}

template <class G>
auto dfs(const G& x, int u) {
  vector<int> a;
  auto vis = createContainer(x, bool());
  dfsLoop(a, vis, x, u);
  return a;
}




// DFS-END
// -------
// Traverses nodes in depth-first manner, listing on exit.

template <class G, class F>
void dfsEndDoLoop(vector<bool>& vis, const G& x, int u, F fn) {
  if (vis[u]) return;  // dont visit if done already!
  vis[u] = true;
  for (int v : x.edges(u))
    if (!vis[v]) dfsEndDoLoop(vis, x, v, fn);
  fn(u);
}

template <class G, class F>
void dfsEndDo(const G& x, int u, F fn) {
  auto vis = createContainer(x, bool());
  dfsEndDoLoop(vis, x, u, fn);
}


template <class G>
void dfsEndLoop(vector<int>& a, vector<bool>& vis, const G& x, int u) {
  dfsEndDoLoop(vis, x, u, [&](int u) { a.push_back(u); });
}

template <class G>
auto dfsEnd(const G& x, int u) {
  vector<int> a;
  auto vis = createContainer(x, bool());
  dfsEndLoop(a, vis, x, u);
  return a;
}
