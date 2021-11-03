#pragma once
#include <vector>
#include <algorithm>
#include "vertices.hxx"
#include "edges.hxx"
#include "csr.hxx"
#include "components.hxx"
#include "pagerank.hxx"
#include "pagerankMonolithicSeq.hxx"

using std::vector;
using std::swap;




auto pagerankLevelwiseWaves(const vector2d<int>& cs, int CM) {
  vector<int> a;
  for (const auto& c : cs) {
    if (a.empty() || a.back()>=CM) a.push_back(c.size());
    else a.back() += c.size();
  }
  return a;
}


template <class T>
inline T pagerankLevelwiseError(T E, int n, int N, int EF) {
  return EF<=2? E*n/N : E;
}




// PAGERANK-LOOP
// --------------

template <class T, class J>
int pagerankLevelwiseSeqLoop(vector<T>& a, vector<T>& r, vector<T>& c, const vector<T>& f, const vector<int>& vfrom, const vector<int>& efrom, int i, J&& ns, int N, T p, T E, int L, int EF) {
  float l = 0;
  for (int n : ns) {
    if (n<=0) { i += -n; continue; }
    T En = pagerankLevelwiseError(E, n, N, EF);
    l   += pagerankMonolithicSeqLoop(a, r, c, f, vfrom, efrom, i, n, N, p, En, L, EF)*float(n)/N;
    swap(a, r);
    i += n;
  }
  swap(a, r);
  return int(l);
}


// Find pagerank of components in topological order (pull, CSR).
// @param x  current graph
// @param xt current transpose graph, with vertex-data=out-degree
// @param q initial ranks (optional)
// @param o options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class G, class H, class T=float>
PagerankResult<T> pagerankLevelwiseSeq(const G& x, const H& xt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  T    p  = o.damping;
  T    E  = o.tolerance;
  int  L  = o.maxIterations, l = 0;
  int  EF = o.toleranceNorm;
  int  CM = o.minComputeSize;
  int  N  = xt.order();
  auto cs = sortedComponents(x, xt);
  auto ns = pagerankLevelwiseWaves(cs, CM);
  auto ks = join(cs);
  auto vfrom = sourceOffsets(xt, ks);
  auto efrom = destinationIndices(xt, ks);
  auto vdata = vertexData(xt, ks);
  vector<T> a(N), r(N), c(N), f(N), qc;
  if (q) qc = compressContainer(xt, *q, ks);
  float t = measureDurationMarked([&](auto mark) {
    fill(a, T());
    if (q) copy(r, qc);
    else fill(r, T(1)/N);
    mark([&] { pagerankFactor(f, vdata, 0, N, p); });
    mark([&] { l = pagerankLevelwiseSeqLoop(a, r, c, f, vfrom, efrom, 0, ns, N, p, E, L, EF); });
  }, o.repeat);
  return {decompressContainer(xt, a, ks), l, t};
}
