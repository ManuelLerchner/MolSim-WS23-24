# Contest sequential performance: Team C

Members of **Team C**:

* Manuel Lerchner
* Tobias Eppacher
* Daniel Safyan

## Code

* Link:     <https://github.com/ManuelLerchner/MolSim-WS23-24>
* Branch:   performance_cluster
* Revision: b878518
* Compiler: gcc 11.2.0

> **Note: The .txt files given in this report can be found on the presentation branch of the repository**

## Starting point

Before we started optimizing the code, we had the following baseline for running our benchmark:

* **Time**: 42.476s
* **Particle Updates**: 235,427 MUP/s

The output of the unoptimized benchmark can be found in the file `MolSim-WS23-24/sheet04/data/Contest1_job_nooptimization.txt`

## Optimization ideas

These ideas were already explored in the previous report, but for convenience here are the
relevant parts

### Lookup table for Lennard-Jones parameters

* Because we usually deal with a little number of distinct particles, we tried to avoid calculating the Lennard-Jones parameters for every particle pair by creating a lookup table with an entry for every pair of the different particle types. But this did not give us the speedup we hoped for:
* On the Linux Cluster we measured:
  * after first idea (data in `MolSim-WS23-24/sheet04/data/Contest1_job_optimized.txt`): 42s 853ms with 233,355 MUP/s

* So our optimization did not work as expected. This may be because the cached results from previous calculations get reused and the lookup table is not used as much as we thought it would be. Another (in our opinion more likely) reason is, that the memory lookup takes at least as long as the calculation (square roots, multiplication...) from scratch.

### Pointer calculation

* We found during the profiling, that the particle== operator takes up a lot of time. This is probably due to the fact that we remove halo particles from the system by finding them in the particle vector which is a linear search. Since we use mostly pointers to particle objects within our implementation, this search can be prevented by using the pointer difference to calculate the particles index in the particle vector and removing the corresponding entry.
* This optimization gave a big speedup as expected. On the Linux Cluster we measured the following:
  * 31s 530ms with 317,158 MUP/s. This is about a 26% speedup compared to the original implementation.

The profiling data that lead to this finding of this optimization possibility is located in the file `MolSim-WS23-24/sheet04/data/profile_contest1_nooptimization.txt`

## Fast math

* Most of the remaining calculation time is spent in the `LinkedCellsContainer::applyPairwiseForces` and `__ieee754_pow_fma` functions. We tried using the "fast math" compiler flag to speed up the calculation of the Lennard-Jones potential and this gave us an additional speedup of 23% on top (on our machines). We hope the benchmark on the cluster finished before the deadline, so we can include the results here.

## SpeedUp

* The optimized pointer calculation yields a runtime of about 74% compared to the original implementation.
* Adding the local gain of the fast-math optimization, theoretically another 23% of the runtime can be cut, reaching as low as ~57% ( = 1.0 * 0.74 * 0.77) of the original runtime.
  * This second optimization has yet to be confirmed on the cluster.

## Conclusion

* Using the pointer calculation and the fast math optimization the major runtime overhead of the Particle== operator and the std::pow function are removed. Which can be seen in the new profiling data(`MolSim-WS23-24/contest1/perf_report_finalOptimization.txt`).
* An additional potential optimization would be a fixed ordering in cell-interactions for pairwise force calculation. That ordering could not only prevent duplicate force application, but would allow us to remove the remaining high costs of the `addAlreadyInfluencedBy()` function, since the corresponding datastructure could then be removed.

### Final result (before the Fast Math optimization)

* Measurement for the contest submission:
  -> **31s 530ms** with **317,158.26 MUP/s**
  
  (theoretical result with fast math using local speedup; not valid for contest until checked) 
  -> **24s 278ms** with **~411,000.00 MUP/s**

## Reproducibility

To make sure everything can be reproduced, here are the instructions, to compile and run the code on the Linux Cluster:

1. Make sure to be on the `performance_cluster` branch
2. Remember to load the modules: `$ source load_CoolMucModules.sh`
3. Following the `build` instructions as described in the README.md to build the benchmarks.
   * Make sure to configure cmake with the `-DCMAKE_BUILD_TYPE=Release` flag. This should be the default but its better to be sure.
4. Switch to the `MolSim-WS23-24/build/benchmarks` directory
5. Submit a job running the `$ ./contest1` executable to the cluster.
