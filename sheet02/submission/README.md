# Sheet 2: Team C

Members of **Team C**:

* Manuel Lerchner
* Tobias Eppacher
* Daniel Safyan

## Code

* Link:     <https://github.com/ManuelLerchner/MolSim-WS23-24>
* Branch:   master
* Revision: <TODO>
* Compiler: gcc 13.1.0 (But should work for most up to date compilers)

## Report

### Task 1: "Unit tests"

0. The addition of `googletest` to our project was pretty straight forward.
1. We added a few unit tests to the project, that check the different functional components:

   ->IO-Elements, Particle-Spawners, Force-Calculation, Particle-Container
2. Then we tested the whole simulation with a few different scenarios
3. In those tests we primarily used the `EXPECT` instead of `ASSERT` macros so the test don`t lead to a crash and all tests can run


### Task 2: "Continuous Integration"

1. The next logical step was to add these unit tests to our already last week existing CI-System 
2. We then also included the `-fsanitize=address` flag to our compile-check to look for memory leaks with every commit
3. Additionally, to protect the master branch, as proposed in the 4th part of the task by looking to organise new features
    in branches and only merge them into master if they are tested and working.


### Task 3: "Logging" <TODO>
1. We already had a lot of output during the execution of our code, so we just had to organise it into different
    log-levels.
2. We agreed on the following log-levels:
    * DEBUG
    * INFO
    * ERROR
3. In addition to that we will give the user the option to write the output to a file instead of the console

### Task 4: "Collision of two bodies"
1. Due to our work from last week, it was quite straight forward to add the Lennard-Jones potential to our Force-Calculation
2. Next, to implement the cuboid spawner, we created a new file format `.cub` that describes these objects and is also able to 
   contain comments. The description can be found in `input/InputFileFormats.md`. Our Particle-Spawner, then takes those
   values from the `CubFileReader` and creates those particles with the initial velocity according to the MaxwellBoltzmannDistribution. So 
   by seperating those functionalities we can easily add new spawners and file formats in the future.
3. Then we ran the example on the worksheet and got the following results:
   - as expected the red cuboid crashes into the blue one and, because the red and blue particles are identical, the red cuboid and
     the part of the blue cuboid that was hit kind of scatter (similar to billiard balls colliding), while the rest of the blue 
      cuboid stays largely in place.
   - also all particles appear to move and oscillate all the time leading to a deformation of the initial cuboid structure. This is more obvious though in a subsequent different
      simulation we ran.
4. We then tried an example with a cuboid that was more than 1 particle wide in the 3rd direction
   - An interesting observation here was, that the cuboids tended to collapse into a sort of sphere (red) or a cylinder (blue)
      even before colliding. We think this is due to the nature of the Lennard-Jones potential, which is attractive at larger
     distances and repulsive at smaller distances. So the particles oscillate around the equilibrium distance and this way 
      leads the particles around the vertices of the cuboid to collapse into a sphere or cylinder.(see the video `cuboid3d.mp4`or `cuboid3dcamera.mp4`)
   
### Misc

* This week we added another command line option. Because our program is primarily used to create a subsequent video, we added the
  `--fps` and `--video_length` options to specify the number of frames per second and length in seconds this video should have.
