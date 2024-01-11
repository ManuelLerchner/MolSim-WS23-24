# Contest sequential performance: Team C

Members of **Team C**:

* Manuel Lerchner
* Tobias Eppacher
* Daniel Safyan

## Code

* Link:     <https://github.com/ManuelLerchner/MolSim-WS23-24>
* Branch:   performance_cluster
* Revision: fd7797d 
* Compiler: gcc 11.2.0 

# Results
these ideas were already explored in the previous report, but for convenience here are the 
relevant parts
## Lookup table for Lennard-Jones parameters

* Because we usually deal with a little number of distinct particles, we could avoid calculating the Lennard-Jones parameters for every particle pair by creating a lookup table with an entry for every pair of the different particle types.
* On the Linux Cluster we measured:
    * before optimization: 42.476s  with 235427 MUP/s (also the data for the contest)
    * after first idea (data in `MolSim-WS23-24/sheet04/data/Contest1_job_optimized.txt`): 42s 853ms with 233355 MUP/s


* So our optimization did not work as expected. This may be because the compiler already reuses the calculations for the mixing rule
  from previous loop iterations and thus the mapping logic just creates additional overhead.

## Pointer calculation 
* We found during the profiling, that the particle== operator takes up a lot of time. This is probably due to the fact that we remove halo particles from the system by finding them in the particle vector which is a linear search. Since we use mostly pointers to particle objects within our implementation, this search can be prevented by using the pointer difference to calculate the particles index in the particle vector and removing the corresponding entry.
* This optimization gave a big speedup as expected. On the Linux Cluster we measured the following: 
  * 31s 530ms with 317.158,26 MUP/s with
  
## SpeedUp
* This becomes a speedup of about 26% compared to the original implementation.
  <img src="./Contest_Speedup.pdf" width="128"/>

## Final result
* Measurement for the contest submission: 
  -> **31s 530ms** with **317.158,26 MUP/s**


## Reproducibility
So everything can be reproduced, here are the instructions, given that the project has been compiled in the 
    `build` directory following the README.md from the root directory:
0. make sure to be on the `performance_cluster` branch
1. remember to load the modules: `$ source load_CoolMucModules.sh`   
2. switch to the `MolSim-WS23-24/build/benchmarks` directory
3. compile the benchmarks: `$ make benchmarks`
4. run the contest1 benchmark: `$ ./contest1`