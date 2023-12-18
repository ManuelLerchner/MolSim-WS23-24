# Sheet <TODO>: Team C

Members of **Team C**:

* Manuel Lerchner
* Tobias Eppacher
* Daniel Safyan

## Code

* Link:     <https://github.com/ManuelLerchner/MolSim-WS23-24>
* Branch:   master
* Revision: <TODO>
* Compiler: gcc 13.1.0 (But should work most up to date compilers)

## Report

### Task 1: Thermostats

1. **Global Scaling of the Temperature**
    * Implementing the scaling was trivial. And it was the same for gradual and instant scaling.

2. **Additional changes to task**
    * We do not have a uniform system initialized velocity, so our spawners can spawn with different initial temperatures.The current Temperature of the system is calculated every iteration to be able to see e.g. temperature distribution over time. We think this is essential for staying true to reality and this will make our simulations be more accurate.
    * We also decided to do so, because the global initial temperature scenario is just a special case.
    * The scaling with a thermostat works identically

### Task 2: Simulation of the Rayleigh-Taylor instability

1. **periodic boundaries**
    * At first, we had the idea to implement periodic boundaries by connecting cells on opposite sides as neighbours, basically forming a cylinder or torus (donut) shape with the (2D-)domain. But this ended up causing more problems and we implemented the boundaries by copying particles in halo cells to the other side.
    * In the process of implementing periodic boundaries, we restructured our boundary implementation in a more elegant way.
    * We divide a boundaries effects in 2 parts: a possible pre-calculation action (like the teleporting halo cells particles to the other side of the domain for periodic boundaries) and a possible condition (like having particles experience a force in the other direction like with reflective boundaries). This allowed more structured optimisations.
2. **Gravity**
    * we now divide forces in simple forces which act globally like gravity in this case and pairwise forces which act between every particle pair.
    * As gravity fell in the simple forces bucket, its calculation was a simple loop.
3. **Lorentz-Berthelot mixing rule**
    * The implementation of these adjustments to the LJ-Potential were also trivial to implement.
4. **Rayleigh-Taylor instability**
    * We have simulated this and the full rendered video can be seen here: [Github Pages](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet04) under the name FluidMixing.mp4.
    * As expected we could observe the less dense fluid shooting out through small paths created by broken symmetries of the denser fluid on top
    * It was exciting to see, that the addition of the mixing rule and differentiation between different particle types could let this, at first complex seeming, effect emerge

### Task 3: Simulation of a falling drop - Liquid

1. **Equilibration**

   The requirement was to be able to checkpoint a system of particles and use it as a starting point for a new simulation.
    * So instead of modelling equilibration as a seperate process and writing the checkpoint into a file to be then read by your actual simulation, we decided to see the equilibration as a pre- or a subsimulation.
    * Now the user can link simulation files as subsimulations to your simulation which will we used to equilibrate your objects before merging them and starting the new simulation. This makes the process of equilibrating more intuitive and faster.
    * This also works recurvively by letting subsimulations have further subsimulations. This way you can intuitivle build large systems by constructing them from smaller pieces. An example can be seen in `/input/subsimulations/multiple_recursive_levels.xml`
2. **Running equilibration and simulation**
    * The file used to generate the falling drop can be found in `falling_drop_equilibrated.xml`
    * We also observed how relevant the temperature was for during the equilibration and simulation. We tried the equilibration first without a thermostat, but this kept making the light fluid evaporate. The thermostat ensures the low temperature and that the fluid stays a fluid.
    * We also tried a simulation with the thermostat turned on and it looked really sad compared to the actual simulation. Like you can see [here](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet04), the video kind of looks like a ball of squishy sand falling on a sandy surface not really having any effect
    * These observations kind of remind us of the different properties that the same material has in different states of matter like solid, fluid and gas, which depend directly on the temperature.
3. **Simulation of a falling drop**
    * The final simulation turned out great, which you can watch [here](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet04) under `FallingDropFancy.mp4`
    * We could really see the big waves caused by the falling droplet, displacing the liquid underneath. This only gives the feeling of a liquid mixing. We also observed waves of different sizes and this resembles reality very well.
    * After the big waves the energy propagates to all particles in the system, distributing itself more and more uniformly as you would also expect in reality
    * Next we made a similar [simulation](https://manuellerchner.github.io/MolSim-WS23-24/submissions/#sheet04) of a drop falling with some horizontal velocity to see more of the periodic boundary. Here you can really see the effect of the periodic boundaries in contrast to reflective ones. This also produced an impressive surfer-like wave.

### Task 4: Performance Measurement and Profiling

1. **Login and modules**
    * This part went largely smoothly
2. **Compiling and linking**
    * Even though the required modules like `xerces-c` or `boost` are loaded, the compiler cannot find and link them.
      **Manuel fixed the Cmake and it worked** <TODO>
3. **Comparable Performance Test**
    * the simulation of 10000 particles took ____s with ____ MUP/s
4. **Profiling**
    * When turning off output, we can get the following profile ____<TODO>
    * So the calculation of ___ and ___ consume the most time

### Task 5: Tuning the sequential Performance
We already implemented a lot of runtime optimizations during the project so thinking of big additional ones was hard. We rejected micro optimisations like inlining or templates, because lots of it can be done better by a compiler with a high optimisation level.
1. **Idea 1**
* Because we usually deal with a little number of different particles, we could avoid calculating the Lennard-Jones parameters for every particle pair by creating a lookup table with an entry for every pair of the different particle types.
* On a native Ubuntu machine we measured:
    * before: ___
    * after: ___


### Misc

* We refractored the code a little. We now have the concept of interceptors. These
  are events that are triggered only once per n iterations. This is useful for `FileOutputWriter`,
  `Thermostat`, etc.
