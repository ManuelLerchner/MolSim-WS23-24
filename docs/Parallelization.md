<!-- markdownlint-disable-next-line -->
\page Parallelization Parallelization

## Overview

The simulation is parallelized using OpenMP, which is automatically used if available on the system.

### DirectSumContainer

If the `DirectSumContainer` is used, the parallelization is done by neglecting the optimization with Newton's third law and calculating the forces between all particles in the container and all particles in the simulation. This allows for a simple parallelization of the force calculation, since the forces between threads never write to the same particle.

### LinkedCellsContainer

For the `LinkedCellsContainer`, there are two parallelization methods available, which can be selected before compiling using the cmake option `PARALLEL_V2_OPT`.:

1. Parallelization by domain splitting (`PARALLEL_V2_OPT=OFF`, default):
    - The simulation domain is split into multiple groups of cells, which ensure that no two threads access the same particles at the same time.
    - Individial groups get executed sequentially. But all cells of that group are updated in parallel using all available threads. 
    - The cell-spacing of this approach assures that two conflicting cells will never be executed concurrently. And therefore no locks or synchronization are needed. 
    - The optimization using Newton's third law is still possible without further complications.
    - This method has basically no overhead. Except a minor reduction in cache locality.

2. Parallelization by particle locking (`PARALLEL_V2_OPT=ON`):
   - Each particle has a lock, which is used to ensure that no two threads access the same particle at the same time.
   - The execution of force calculations is randomized: A random cell is picked which calculates all the forces for its particles
   - During each update both affected particles are locked. 
   - The randomization helps to pick mostly indepent particle pairs so that the wait time for each thread is kept small.
   - The drawback of this method is the overhead due to the locking of the particles
