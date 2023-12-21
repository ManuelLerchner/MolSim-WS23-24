# Sheet 4: Team C

Members of **Team C**:

* Manuel Lerchner
* Tobias Eppacher
* Daniel Safyan

## Code

* Link:     <https://github.com/ManuelLerchner/MolSim-WS23-24>
* Branch:   master
* Revision: 335f831
* Compiler: gcc 13.1.0 (But should work with most up to date compilers)

> **IMPORTANT**: The optimization is on the `performance_cluster` branch. And has not been merged into master yet. So please switch to that branch to see the optimization.

## Report

### Task 1: Thermostats

1. **Global Scaling of the Temperature**
    * Implementing the scaling was trivial. And it was the same for gradual and instant scaling, appart from clamping the temperature change to the maximum difference specified in the input file.

2. **Additional changes to task**
    * We do not have a uniform globally initialized velocity, so our spawners can spawn groups of particles with different initial temperatures.
    * We also decided to do so, because the global initial temperature seemed like a rather special scenario.
    * It is also possible to specify the initial temperature even if there is already velocity in the system. Forbidding that would have required extra code and also artificially limit the users input possibilities which seemed unnecessary to us.

### Task 2: Simulation of the Rayleigh-Taylor instability

1. **Periodic boundaries**
    * At first, we had the idea to implement periodic boundaries by connecting cells on opposite sides as neighbours and using a special transformation on the particles coordinates during force calculation. This should be equivalent of mapping the particles positions onto the surface of a cylinder or torus (on which opposite sides are adjacent). In our opinion this method would be faster, than the one suggested in the introduction of this assignment, since lots of expensive memory allocations and frees for halo particles would be avoided. Sadly the math turned out to more elaborate than we thought and the implementation in our codebase seemed to harder than expected. Therefore we decided on using the suggested implementation by copying particles in halo cells to the other side.
    * In the process of implementing periodic boundaries, we restructured our boundary implementation in a more elegant way.
    * We divide a boundaries effects in 2 parts: a possible pre-calculation action (like the teleportation of halo cells particles to the other side of the domain for periodic boundaries) and the actual boundary condition (like having particles experience a force in the other direction like with reflective boundaries). This allowed more structured optimisations.
2. **Gravity**
    * we now divide forces in simple forces which act globally like gravity in this case and pairwise forces which act between every particle pair.
    * As gravity fell in the simple forces bucket, its calculation was a simple loop.
3. **Lorentz-Berthelot mixing rule**
    * The implementation of these adjustments to the LJ-Potential were trivial to implement.
    * The particles now simply hold the additional epsilon and sigma values used in the Lennard-Jones potential. Those values are assigned via the particle spawners input values.
    * The Lennard-Jones potential then calculates the combined Lennard-Jones parameters of both its input particles and uses those values.
4. **Rayleigh-Taylor instability**
    * We have simulated this and the full rendered video can be seen here: [Github Pages](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet04) under the name FluidMixing.mp4.
    * As expected we could observe the less dense fluid shooting out through small paths created by broken symmetries of the denser fluid on top
    * It was exciting to see, that the addition of the mixing rule and differentiation between different particle types could let this, at first complex seeming, effect emerge

### Task 3: Simulation of a falling drop - Liquid

1. **Equilibration**

   The requirement was to be able to checkpoint a system of particles and use it as a starting point for a new simulation.
    * So instead of modelling equilibration as a seperate process and writing the checkpoint into a file to be then read by your actual simulation, we decided to see the equilibration as a pre- or a subsimulation.
    * Now the user can link other xml input files as subsimulations to another simulation. Those subsimulations will be automatically executed before the start of the "parent"-simulation and their final particle states saved into checkpoint files. Those particle states are simply copied into the simulation and used as starting points for further simulation.
    * This works also recurvively by letting subsimulations have further subsimulations. This way you can intuitively build large systems by constructing them from smaller pieces. An extreme example can be seen in `/input/subsimulations/multiple_recursive_levels.xml`
      * The file defines two subsimulations, which then have subsimulations again and so on. The resulting computation tree looks like this:
        * Multiple recursive levels `[main simulation]`
          1. Top Left `[first simulation at depth 1]`
             * Sphere Spawner
             1. Right center `[first simulation at depth 2]`
                * Sphere spawner
                1. Top Right `[first simulation at depth 3]`
                   * Sphere spawner
                2. Bottom Right `[second simulation at depth 3]`
                   * Sphere spawner
                   1. Center Center `[first simulation at depth 4]`
                      * Sphere spawner
          2. Bottom Left `[second simulation at depth 1]`
             * Sphere spawner

    When running the simulation, the effects of the equilibration can be seen directly, because the deeper a simulation is in the tree, the more time it had to equilibrate and is therefore generally more spread out.

    * Each subsimulation can have its own settings, and even allows for file output. This can be used to debug the equilibration process. Furthermore there exists a caching mechanism, which reloads the final equilibration state from a `.chkpt` (checkpoint) file, if the simulation is run again.
      * The system is actually quite intelligent as it automatically detects if the input file has deviated from the checkpoint file (it does this by comparing the hash of the input file with the hash stored of the checkpoint file). This helps to avoid unwanted cache loads or unnecessary resimulations.

2. **Running equilibration and simulation**
    * The file used to generate the falling drop can be found in `falling_drop_equilibrated.xml`
    * We also observed how relevant the temperature was for during the equilibration and simulation. We tried the equilibration first without a thermostat, but this kept making the light fluid "evaporate". The thermostat ensures the low temperature and that the fluid stays a fluid.
    * We also tried a simulation with the thermostat turned on and it looked really sad compared to the actual simulation. Like you can see [here](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet04), the video kind of looks like a ball of squishy sand falling on a sandy surface not really having any effect
    * These observations kind of remind us of the different properties that the same material has in different states of matter like solid, fluid and gas, which depend directly on the temperature.
    * 
3. **Simulation of a falling drop**
    * The final simulation turned out great, which you can watch [here](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet04) under `FallingDropFancy.mp4`
    * We could really see the big waves caused by the falling droplet, displacing the liquid underneath. This only gives the feeling of a liquid mixing. We also observed waves of different sizes and this resembles reality very well.
    * After the big waves the energy propagates to all particles in the system, distributing itself more and more uniformly as you would also expect in reality
    * Next we made a similar [simulation](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet04) of a drop falling with some horizontal velocity to see more of the periodic boundary. Here you can really see the effect of the periodic boundaries in contrast to reflective ones. This also produced an impressive surfer-like wave.
    * We also found out that you can stack different glyph types on top of each other to show the different particle types aswell as the forces acting on them, if you tweak the colors right the video can look really cool.

### Task 4: Performance Measurement and Profiling

1. **Login and modules**
    * This part went largely smoothly we were able to log in and load the required modules.
2. **Compiling and linking**
    * We had some trouble in this part. Even though the required modules like `xerces-c` or `boost` were loaded, the compiler couldn't find and link them.
    * After some trial and error we managed to fix this by using the cmake command `find_package` for the troublesome libraries which seemed to solve the problem for us.
3. **Comparable Performance Test**
    * We decided to use a 10000 particle cuboid without any thermostat or force acting globally as performance test. The exact program can be found in `/benchmarks/2DPartRect/2D_task4.cpp`.
    * The simulation of 10000 particles took 35.376s on the Linux Cluster with 282960 MUP/s
    * The whole data can be found in `sheet04/data/Task4_job_output.txt`.

4. **Profiling**
    * When turning off output, we can get the profile as shown in `/benchmarks/profiles/profile_task4.txt`
    * So the calculation of the pairwise consume the most time as expected

### Task 5: Tuning the sequential Performance

We already implemented a lot of runtime optimizations during the project so thinking of big additional ones was hard. We reject micro optimizations like inlining or templates, because lots of it can be done better by a compiler with a high optimization level and it messes up our code.

1. **Idea:**

* Because we usually deal with a little number of different particles, we could avoid calculating the Lennard-Jones parameters for every particle pair by creating a lookup table with an entry for every pair of the different particle types.
* On the Linux Cluster we measured:
  * before optimization: 42.476s  with 235427 MUP/s (also the data for the contest)
  * after first idea (data in `sheet04/data/Contest1_job_optimized.txt`): 42s 853ms with 233355 MUP/s 


* So our optimization did not work as expected. This may be because the compiler already reuses the calculations for the mixing rule 
from previous loop iterations and thus the mapping logic just creates additional overhead.

* We also found during the profiling, that the particle== operator takes up a lot of time. This is probably due to the fact that we remove halo particles from the system by finding them in the particle vector which is a linear search. Since we use mostly pointers to particle objects within our implementation, this search can be prevented by using the pointer difference to calculate the particles index in the particle vector and removing the corresponding entry.
* Additionally the addAlreadyInfluencedBy() method seems to take a disproportionate amount of time for what it actually should do. Since it is simply a insert into an std::unordered_map, we think that the hash function is the bottleneck here. We tried std::vector to replace the unordered_map, but the following linear lookup was too slow. Other data structures could potentially fix this problem, but we did not have the time to try them out.

### Contest 1

* We tried the program out on the linux cluster and it took 42.476s with 235427 MUP/s (data in `sheet04/data/Contest1_job_nooptimization.txt`).
* The performance will be tuned more though until the actual contest deadline on 5 January.
### Misc

* We refractored the code a little. We now have the concept of interceptors. These
  are events that are triggered only once per n iterations. This is useful for `FileOutputWriter`, `Thermostat`, `Progress Bar`, and `Data Logging`.
  Grouping these types of functionalities like this seems more elegant to us will help us in the next sheet where we want different ways of extracting internal data statistics from the simulation.
