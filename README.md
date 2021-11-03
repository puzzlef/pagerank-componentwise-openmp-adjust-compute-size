Comparing various **min. compute sizes** for topologically-ordered components
([levelwise]) PageRank ([pull], [CSR]).

`TODO!`

This experiment was for comparing performance between [levelwise] pagerank
with various **min. compute size**, ranging from `1` - `1E+7`. Here,
**min. compute size** is the minimum no. nodes of each pagerank compute using
standard algorithm ([monolithic]). Each **min. compute size** was attempted on
different types of graphs, running each size 5 times per graph to get a good
time measure. **Levelwise** pagerank is the [STIC-D algorithm], without
**ICD** optimizations (using single-thread). Although there is no clear
winner, it appears a **min. compute size** of `10` would be a good choice.
Note that *levelwise* approach does not make use of *SIMD instructions* which
are available on all modern hardware.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. This experiment was done with guidance
from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 69532892 {} (loopDeadEnds)
# order: 4847571 size: 69532892 {} (transposeWithDegree)
# [12472.006 ms; 058 iters.] [0.0000e+00 err.] pagerankMonolithic
# [10593.825 ms; 047 iters.] [4.7413e-06 err.] pagerankLevelwise [1e+00 min-compute-size]
# [10096.874 ms; 048 iters.] [4.0675e-06 err.] pagerankLevelwise [5e+00 min-compute-size]
# [10145.596 ms; 048 iters.] [4.7744e-06 err.] pagerankLevelwise [1e+01 min-compute-size]
# [10102.019 ms; 049 iters.] [4.2481e-06 err.] pagerankLevelwise [5e+01 min-compute-size]
# [10302.962 ms; 049 iters.] [4.9025e-06 err.] pagerankLevelwise [1e+02 min-compute-size]
# [10604.037 ms; 050 iters.] [4.2373e-06 err.] pagerankLevelwise [5e+02 min-compute-size]
# [10284.720 ms; 050 iters.] [4.1973e-06 err.] pagerankLevelwise [1e+03 min-compute-size]
# [10556.456 ms; 050 iters.] [4.1276e-06 err.] pagerankLevelwise [5e+03 min-compute-size]
# [10818.184 ms; 051 iters.] [4.8086e-06 err.] pagerankLevelwise [1e+04 min-compute-size]
# [11492.941 ms; 051 iters.] [4.4000e-06 err.] pagerankLevelwise [5e+04 min-compute-size]
# [11201.286 ms; 051 iters.] [3.7668e-06 err.] pagerankLevelwise [1e+05 min-compute-size]
# [11985.655 ms; 056 iters.] [4.2787e-06 err.] pagerankLevelwise [5e+05 min-compute-size]
# [12221.266 ms; 056 iters.] [5.1053e-06 err.] pagerankLevelwise [1e+06 min-compute-size]
#
# ...
```

[![](https://i.imgur.com/d7a2KUv.png)][sheets]
[![](https://i.imgur.com/N5GTokT.png)][sheets]
[![](https://i.imgur.com/a02NaHs.png)][sheets]
[![](https://i.imgur.com/6BqYmGp.png)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/5gcO8cg.jpg)](https://www.youtube.com/watch?v=4Xw0MrllRfQ)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[monolithic]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/KgBUFkTrHGB4WBfs9
[sheets]: https://docs.google.com/spreadsheets/d/10KhCjLln713-qWsQMURTQKmQsniTO0xwGzNeQkuV3sE/edit?usp=sharing
