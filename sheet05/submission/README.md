# Sheet 5: Team C

Members of **Team C**:

* Manuel Lerchner
* Tobias Eppacher
* Daniel Safyan

## Code

* Link:     <https://github.com/ManuelLerchner/MolSim-WS23-24>
* Branch:   master
* Revision: <TODO>
* Compiler: gcc 13.1.0 (But should work with most up to date compilers)

[//]: # (> **IMPORTANT**: The optimization is on the `performance_cluster` branch. And has not been merged into master yet. So please switch to that branch to see the optimization.)

## Report

### Task 1: Simulation of a membrane

1. **Membrane implementation**
   * To implement the membrane functionality, we just extended the particle class by a connected particles tuple. 
It stores all information needed to calculate the force, which creates our membrane.
   * The force calculation is done by an additional simple force `HarmonicForce`. It loops over the neighbors and calculates the force 
holding the particle in its place in the membrane
   


2. **Simulation of a 2D-cloth in 3D**
    * The simulation was supposed to look like one particle was picked up and then dropped again, so we added the additional `TargettedTemporaryConstantForce`. 
Its only use is for this kind of simulation. Using it, you can set a duration for which your specified force vector will be applied to a 
specified set of particles. 
    * So in the end the simulation [`membrane_cloth.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05)
looked precisely as expected. The membrane deforms just like a cloth would when picking it up and then creates waves after falling down on the ground.

3. **Additions**
   * In these membrane simulations it is really hard to fit in outflow boundaries, because the membrane works as a coherent structure and the deletion of
single particles leads to segmentation faults and bad pointers. We deal with this problem just by refusing to run the simulation and giving an error message. We decided to do so, 
because we figured that an outflow boundary just does not make a lot of sense in the same setting as membranes 
   * We did not have these problems with reflective or even periodic boundaries. An example of a simulation done with periodic boundaries is the video called [`membrane_periodic_cloth.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05).
   

### Task 2: Parallelization

1. **Domain partitioning**
   * Domain partitioning is our first parallelization method. It works just like our second method by creating a calculation order for the pairwise forces in `LinkedCellsContainer::initIterationOrders`. 
We then assign threads one of the domains and make sure that they don't intersect, so we can calculate in parallel. This works really well and is quicker than the second option.
   * We also had great success in tuning the runtime after setting omp schedule to dynamic.
   * We found the idea and scheme for going through the domains in <TODO> 


2. **Particle Locking**
    * This method is simpler but almost as fast as the first one. Here we use mutexes to ensure that no two threads are working on the same calculation at the same time and run into race conditions.
    * We then assign every thread a random particle to calculate the force for, that is not already occupied by another thread. 
    * This method is slower because sometimes threads have to wait for a particular mutex to be unlocked and tus have to just wait for another thread. 
    * Another interesting observation was, that due to the randomness of the order a large chaotic system can be created with the same starting conditions, 
end up differently every time, due to floating point rounding errors. You can observe it in the [`parallelization_chaotic_system_particle_locking.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) video, where we ran the same simulation a bunch of times and overlayed the different runs. 

3. **Performance-Tests**
   * We ran the performance tests on the Linux Cluster and wanted to see how the number of threads affects the runtime. We plotted a bunch of graphs and the raw data for them is in the `/../data` folder.
   * If you now compare [`Rayleigh_Taylor_3D_Speedup_Comparison.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) and [`Rayleigh_Taylor_3D_Speedup_Comparison_v2.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) you would think that the speedup is almost identical for both methods. But the V2 speedup is overestimated, because
in [`Rayleigh_Taylor_3D_Time_Comparison.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) and [`Rayleigh_Taylor_3D_Time_Comparison_v2.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) you can see that the runtime for the particle locking method is actually twice as high as for the domain partitioning.
   * We believe it is, because in our benchmark we get the original runtime by running the simulation with one thread. So in V2 the whole overhead of the usage of mutexes overestimates the original runtime leading to overblown speedup numbers.
   * To get an in depth profile of the program, we ran vtune and seem to have optimised the parallelization quite well, as seen in [`VTuneHotspots_Parallelization_V1.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) and the `/../data/vtune*/` folder.
   

### Task 3: Rayleigh-Taylor Instability in 3D

To get this result we ran the following: 
   * <TODO> create a contest2.cpp to just run end get the results for 42 threads and 1000 iterations


**Results**
Our fastest run was with 42 threads and this is the data since there was no thread limit.
* 31,228 seconds
* 3 202 152 MUP/s




### Task 4: Nano-scale flow simulation 
The main task we focused on was Option B but here are our option A results:
1. **Implementation**
   * The creation of velocity measurements fitted nicely into our interceptor concept so implementing it was straight forward. 
The same was for the new thermostat.
   * The fixed particles were implemented by a single flag which can be set in the input file.

2. **Simulations**
   * The first simulation we ran was without any obstacle accelerated by gravity and named [`nano_scale_flow_short.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05). 
Its velocity profile, [`nano_Velocity_Profile_No_Obstacle.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05), looks smooth as expected.
All curves (representing the different times) seem to accelerate evenly.
   * The second simulation was with a fixed cuboid obstacle on the side and named [`nano_scale_flow_short_obstacle_cuboid.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05).
Its velocity profile, [`nano_scale_flow_short_obstacle_cuboid.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05), seems to be held up starting approximately at iteration (time) 12000.
So a lot of particles are held up by a cuboid, so we wanted to try to see the effects of another shape.
   * The third simulation was with a fixed sphere obstacle on the side and named [`nano_scale_flow_short_obstacle.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05).
In its velocity profile, [`nano_Velocity_Profile_Sphere_Obstacle.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05), we can see how the flow is not as abruptly held up as from the cuboid.
   * The fourth simulation was due to the thought of distiguishing between laminar and turbulent flow. We remembered that the Reynolds number is a good indicator for that and is higher for higher velocities. 
So we ran a simulation with a higher velocity and a cuboid object and named it [](). We wanted to see how the initial velocity affects the flow and the velocity profile in the end.
...<TODO>...

### Task 5: Crystallization of Argon


1. **Implementation:**

* The smoothed LJ was just a small straight forward adjustment to our code. 
* The Diffusion, Temperature and RDF measurements were all implemented as interceptors.

2. **Simulations:**
* We ran a few simulations for a small and a large system. They all can be found at our [github pages website](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) but we think that `argon_big_comparison.mp4` shows the effect the best(although it took very long to run...).
* We can observe how the supercooling leads to more but smaller holes in the gas and you can also observe this in the quantitative analysis. In [`ArgonRDF_SuperCooling.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) you can see a huge spike 
in local density in contrast to the slow cooling plot. Also in the diffusion plot [`ArgonDiffusion.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) you can clearly see how strongly Diffusion and Temperature are correlated, when you compare this plot to the Temperature history.
* The crystallization effect should occur around 87.3 K because this is when argon is cooled below its boiling point and this is also about what we observe. We see how the crystallization forms early for the supercooling argon about at iteration 
29000 agreeing with the boiling point of 87.3 K and the temperature plot.




### Misc

* The 3D Rayleigh-Taylor Instability simulation can be found in [`rayleigh_taylor_instability_3d.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05)
* We also inlined our functions more which led to a speedup, which we did not quantify. We originally thought the compiler would do that for us, but apparently doing it manually still has at least some positive effect. 
