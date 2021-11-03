#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(const G& x, const H& xt, int repeat) {
  enum NormFunction { L0=0, L1=1, L2=2, Li=3 };
  vector<float> *init = nullptr;

  // Find pagerank using default options.
  auto a0 = pagerankMonolithicSeq(xt, init, {repeat});
  auto e0 = l1Norm(a0.ranks, a0.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankMonolithicSeq\n", a0.time, a0.iterations, e0);

  // Find pagerank using L1-norm for convergence check.
  auto a1 = pagerankMonolithicSeq(xt, init, {repeat, L1});
  auto e1 = l1Norm(a1.ranks, a0.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankMonolithicSeqL1Norm\n", a1.time, a1.iterations, e1);
  for (int CM=1, i=0; CM<x.order(); CM*=i&1? 2:5, i++) {
    auto a2 = pagerankLevelwiseSeq(x, xt, init, {repeat, L1, CM});
    auto e2 = l1Norm(a2.ranks, a0.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankLevelwiseSeqL1Norm [min-compute-size=%.0e]\n", a2.time, a2.iterations, e2, (double) CM);
  }

  // Find pagerank using L2-norm for convergence check.
  auto a3 = pagerankMonolithicSeq(xt, init, {repeat, L2});
  auto e3 = l1Norm(a3.ranks, a0.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankMonolithicSeqL2Norm\n", a3.time, a3.iterations, e3);
  for (int CM=1, i=0; CM<x.order(); CM*=i&1? 2:5, i++) {
    auto a4 = pagerankLevelwiseSeq(x, xt, init, {repeat, L2, CM});
    auto e4 = l1Norm(a4.ranks, a0.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankLevelwiseSeqL2Norm [min-compute-size=%.0e]\n", a4.time, a4.iterations, e4, (double) CM);
  }

  // Find pagerank using Li-norm for convergence check.
  auto a5 = pagerankMonolithicSeq(xt, init, {repeat, Li});
  auto e5 = l1Norm(a5.ranks, a0.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankMonolithicSeqLiNorm\n", a5.time, a5.iterations, e5);
  for (int CM=1, i=0; CM<x.order(); CM*=i&1? 2:5, i++) {
    auto a6 = pagerankLevelwiseSeq(x, xt, init, {repeat, Li, CM});
    auto e6 = l1Norm(a6.ranks, a0.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankLevelwiseSeqLiNorm [min-compute-size=%.0e]\n", a6.time, a6.iterations, e6, (double) CM);
  }
}


int main(int argc, char **argv) {
  char *file = argv[1];
  int repeat = argc>2? stoi(argv[2]) : 5;
  printf("Loading graph %s ...\n", file);
  auto x  = readMtx(file); println(x);
  // Handle dead ends with loop strategy (alternatives: loop-all, remove).
  selfLoopTo(x, [&](int u) { return isDeadEnd(x, u); });
  print(x); printf(" (selfLoopDeadEnds)\n");
  // Transpose graph after handling dead ends.
  auto xt = transposeWithDegree(x); print(xt); printf(" (transposeWithDegree)\n");
  runPagerank(x, xt, repeat);
  printf("\n");
  return 0;
}
