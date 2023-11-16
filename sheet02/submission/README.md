# Sheet 2: Team C

Members of **Team C**:

* Manuel Lerchner
* Tobias Eppacher
* Daniel Safyan

## Code

* Link:     <https://github.com/ManuelLerchner/MolSim-WS23-24>
* Branch:   master
* Revision: 3131eaeb9ff97b7d783fcd234a06f4e799db8985   (or checkout tag: "Submission-2")
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

### Task 3: "Logging"

1. We already had a lot of output during the execution of our code, but were still using the standard output to log it in the console. Also there was no clear distinction between error messages or simple information printing. With the addition of the spdlog library, we organised the output into different log-levels and could make use of the available formatting options for a clear output.
2. We currently use the following log-levels:
   * DEBUG: Information not needed for normal program usage. It is currently only used to log con-/destruction of particle objects.
   * INFO: Most of our general ouput uses this output, such as the recap of the used simulation parameters or the current progress.
   * ERROR: General errors that result in a stop of the program execution, such as errors in input files or mistakes in the CLI.
   * CRITICAL: Only used once, to report the termination of the program because of errors in the input file.
3. The user can select the log-level via the command line option `-l` or `--log_level`. Possible values are in general the names of the log-level in lowercase or simple no output with `off`:
   * `off`, `critical`, `error`, `info`, `debug`, `trace`
   * The option `off` results in no output at all.
   * All other options yield more and more output, as each level includes the output of the preceding one, with `critical` logging the least and `trace` the most amount of information.
4. In the future we could give the user the option to write the output to a file instead of the console.

### Task 4: "Collision of two bodies"

1. Due to our work from last week, it was quite straight forward to add the Lennard-Jones potential to our Force-Calculation
2. Next, to implement the cuboid spawner, we created a new file format `.cub` that describes these objects and is also able to
   contain comments. The description can be found in `input/InputFileFormats.md`. Our Particle-Spawner, then takes those
   values from the `CubFileReader` and creates those particles with the initial velocity according to the MaxwellBoltzmannDistribution. So
   by seperating those functionalities we can easily add new spawners and file formats in the future.
3. Then we ran the example on the worksheet and got the following results:
   * as expected the red cuboid crashes into the blue one and, because the red and blue particles are identical, the red cuboid and
     the part of the blue cuboid that was hit kind of scatter (similar to billiard balls colliding), while the rest of the blue
      cuboid stays largely in place.
   * also all particles appear to move and oscillate all the time leading to a deformation of the initial cuboid structure. This is more obvious though in a subsequent different
      simulation we ran.
4. We then tried an example with a cuboid that was more than 1 particle wide in the 3rd direction
   * An interesting observation here was, that the cuboids tended to collapse into a sort of sphere (red) or a cylinder (blue)
      even before colliding. We think this is due to the nature of the Lennard-Jones potential, which is attractive at larger
     distances and repulsive at smaller distances. So the particles oscillate around the equilibrium distance and this way
      leads the particles around the vertices of the cuboid to collapse into a sphere or cylinder.(see the video `cuboid3d.mp4`or `cuboid3dcamera.mp4`)
5. Time Measurement: The simulation took 113.058 seconds to run on one of our machines. This measurement was taken after commenting out the code for file and logging output and only around the main simulation loop. The measurement was done using the `std::chrono` library. The hardware specifications were: 
   * Processor	12th Gen Intel(R) Core(TM) i5-12600   3.30 GHz
   * RAM	16,0 GB (15,7 GB usable)
   * System type:	Windows 11, 64-bit operating system, x64-based processor
   * Measurement executed in WSL2 Ubuntu 22.04 LTS


### Misc

* This week we added another command line option. Because our program is primarily used to create a subsequent video, we added the
  `--fps` and `--video_length` options to specify the number of frames per second and length in seconds this video should have.
* We added a cmake-target to automatically format all the code in the repo. Together with a github action this should automatically fix and then commit formatting issues.
* We changed the cmake-structure to use the cmake-modules folder instead of putting everything into one big file
