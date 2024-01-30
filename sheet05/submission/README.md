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
   * To implement the membrane functionality, we just extended the particle class by a connected particles vector. 
It stores all information needed to calculate the harmonic force, which realizes our membrane behaviour.
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
The Domain Partitioning queue is a `std::vector` of `std::vector`'s of Cells. From a [paper](https://www.researchgate.net/profile/Fabio-Gratl/publication/357143093_N_Ways_to_Simulate_Short-Range_Particle_Systems_Automated_Algorithm_Selection_with_the_Node-Level_Library_AutoPas/links/649acc9cc41fb852dd355f24/N-Ways-to-Simulate-Short-Range-Particle-Systems-Automated-Algorithm-Selection-with-the-Node-Level-Library-AutoPas.pdf) we selected the c_18 partitioning. Its strength is that it utilizes Newton and only calculates in front of it. 
So we partition the Cells in a queue of 18 sets. These sets can be calculated completely in parallel without having to worry about race conditions. This works really well and is quicker than the second option.
   * We also had great success in tuning the runtime after setting omp schedule to dynamic.
   


2. **Particle Locking**
    * This method is simpler, here we use mutexes to ensure that no two threads are working on the same particle at the same time and run into race conditions.
    * Each threads can then calculate the forces for one cell and still utilize Newtons third law, since race conditions are avoided.
    * This method is slower because of the overhead produced by the lock/unlock operations. Additionally, threads might have to wait for a particular mutex to be unlocked and thus have to wait for another thread to finish its calculation. 
    * Another interesting observation was, that due to the randomness of the order a large chaotic system can be created with the same starting conditions, 
end up differently every time, due to floating point rounding errors. You can observe it in the [`parallelization_chaotic_system_particle_locking.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) video, where we ran the same simulation a bunch of times with different thread counts and overlayed the different runs. 

3. **Performance-Tests**
   * We ran the performance tests on the Linux Cluster and wanted to see how the number of threads affects the runtime. We plotted a bunch of graphs and the raw data for them is in the `../data` folder.
   * If you now compare the graphs in [`Rayleigh_Taylor_3D_Speedup_Comparison.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05), the speedup is almost identical for both methods, which is misleading when analysing the performance. Despite the rather similar speedup, the graphs in [`Rayleigh_Taylor_3D_Time_Comparison.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) show, that the runtime for the particle locking method is actually around twice as high as for the domain partitioning.
   * The reason for this is the definition of speedup, as it depends on the single thread performance. Using particle locking, the overhead caused by mutexes increases the single threaded runtime, leading to better speedup numbers when executing with higher thread counts.
   * To get an in depth profile of the program, we ran vtune and seem to have optimised the parallelization quite well, as seen in [`VTuneHotspots_Parallelization_V1.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) and the `/../data/vtune*/` folder.
   * On the CoolMUC the MUP/s plummet for more than 42 threads for both versions as seen in [`Rayleigh_Taylor_3D_MUPs_Comparison.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) . This 
seems to be the point where the overhead of each thread starts to exceed its usefulness, at least for the Contest2 example and for this particular Linux Cluster, so we don't think that this is a general limit of these methods. Simulation containing more particles in a bigger domain with more cells would probably still profit from a further increase in thread counts.
   * After we additionally used the intel compiler instead of gcc, the code got even faster. CoolMUC runs on Intel CPUs, so it is not too surprising to see that in the comparison [`Rayleigh_Taylor_3D_MUPs_Comparison.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) the MUP/s are higher when compiling with ICPX.

### Task 3: Rayleigh-Taylor Instability in 3D

**To get this result we ran the following:**
   * You compile all benchmarks as described in the root README.md
   * Then for this particular case you can run `./Contest2`. When testing on the CoolMUC, make sure that you are able to use at least 42 threads (in our case we used the cluster `teramem-inter`).



**Results:**

Our fastest run for the first 1000 iterations of the example `Rayleigh-Taylor Instability 3D`, was done using 42 threads and the intel compiler on the `teramem-inter`-cluster.
* 19.25 seconds
* 5 193 668 MUP/s

For the reevaluation of the example for contest 1 we achieved times in the 1-2 second range. Again with 42 threads and the ICPX compiled program on the `teramem-inter`-cluster.


### Task 4: Nano-scale flow simulation 
The main task we focused on was Option B, but we also implemented the features requested in option A:
1. **Implementation**
   * The creation of velocity measurements fitted nicely into our interceptor concept so implementing it was straight forward. 
The same was for the new thermostat.
   * The fixed particles were implemented by a single flag which can be set in the input file for each particle spawner seperately.

2. **Simulations**
   * The first simulation we ran was without any obstacle accelerated by gravity and named [`nano_scale_flow_short.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05). 
Its velocity profile, [`nano_Velocity_Profile_No_Obstacle.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05), looks smooth as expected, and shows lower velocities at the walls of the tube (caused by some kind of friction).
The curves, representing the different timeframes, seem to show this fact more clearly over time.
   * The second simulation was with a fixed cuboid obstacle on the side and named [`nano_scale_flow_short_obstacle_cuboid.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05).
Its velocity profile, [`nano_scale_flow_short_obstacle_cuboid.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05), seems to be held up starting approximately at iteration (time) 12000.
So a lot of particles are held up by a cuboid, so we wanted to try to see the effects of another shape.
   * The third simulation was with a fixed sphere obstacle on the side and named [`nano_scale_flow_short_obstacle.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05).
In its velocity profile, [`nano_Velocity_Profile_Sphere_Obstacle.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05), we can see how the flow is not as abruptly held up as by the cuboid.
   * The fourth simulation was due to the thought of distinguishing between laminar and turbulent flow. We remembered that the Reynolds number is a good indicator for that and is higher for higher velocities. 
So we ran a simulation [`reynolds.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) with a higher initial velocity and a cuboid object. That simulation can be fond at `input/nano_scale_flow/nano_scale_flow_higher_reynolds_number.xml`. We wanted to see how the initial velocity affects the flow and the velocity profile in the end.
But this did not really work out. We did not really get turbulent flow and the periodic boundaries on the bottom and top created just a completely noisy picture, that didn't even look like a flow. At some point in time the flow transitioned into more of a brownian motion due to the top and bottom particles bumping into each other through the periodic boundary. Before that there were some things that looked like 
little swirls with some imagination, but not really explicit turbulent flow.

### Task 5: Crystallization of Argon


1. **Implementation:**

* The smoothed LJ was just a small straight forward adjustment to our code. 
* The Diffusion, Temperature and RDF measurements were all implemented as interceptors.

2. **Simulations:**
* We ran a few simulations for a small and a large system. They all can be found at our [github pages website](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) but we think that `argon_big_comparison.mp4` shows the effect the best (although it took a bit longer to run...).
* We can observe how the supercooling leads to more but smaller holes in the structure and you can also observe this in the quantitative analysis. In [`ArgonRDF_SuperCooling.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) the spikes in local density are not as regular as the ones in the slow cooling plot. This is an indicator for a more unsorted structure emerging when super-cooling. Also in the diffusion plot [`ArgonDiffusion.png`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05) you can clearly see how strongly diffusion and temperature are correlated, when you compare this plot to the temperature history.
* The crystallization effect should occur around 87.3 K because this is when argon is cooled below its boiling point and this is also about what we observe. We see how the crystallization forms early for the supercooling argon about at iteration 
29000 agreeing with the boiling point of 87.3 K and the temperature plot.




### Misc

* The 3D Rayleigh-Taylor Instability simulation from Contest 2 can be found in [`rayleigh_taylor_instability_3d.mp4`](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet05)
* We also inlined our functions more which led to a speedup, which we did not quantify. We originally thought the compiler would do that for us, but apparently doing it manually still has at least some positive effect. 
