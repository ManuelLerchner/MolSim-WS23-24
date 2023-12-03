# Sheet <TODO>: Team C

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

### Task 1: XML-Input

1. **Create a schema**
    - We created a schema for the input format, which you can find in 'input/simulation.xsd'
    - It was pretty straight forward and the most important thing was to make sure to not forget any parameter
    - Then with the help of the xsd-compiler we quickly had our xml-parser
    
2. **Create adapters for different elements**
    - we continue to use the adapter pattern to avoid complex code and to have all value verifications in one place
    - example: you have parsed a xsd-cuboid and can convert it to a cuboid spawner

### Task 2: Linked-Cell-Algorithm

1. **Data structure**
    - The hardest part was to make it work with boundary conditions, so in the end it just became a 6-tuple
    - We then gave the Linked-Cells-Container a way to iterate over all particles, boundary cells, halo cells, occupied cells ...
    - The reason we did this is that it enables us to optimize our code a lot
    - For example: Do not iterate over unoccupied cells

2. **Force calculation**
   - The force calculation is a nested loop over cells
   - Then we calculate the force and reaction force in the cell itself
   - Then we consider the interactions between our cell and its neighbors (every cell has a list of all neighboring cells so we can make use of the cutoff radius)
after checking if they are in the cutoff radius

3. **Optimizations**
    - We already made use of Newtons third law in the force calculation inside of a cell
and now we use it to optimize force calculation between cells
    - The problem was that if we implement it naively we end up adding the same force
interaction multiple times for each particle
    - So to avoid that we save an already influenced by list for each cell, so we can use Newton
and just skip a cell if it is inside or already influenced list
4. **Observations of the simulation**
   - We reran the simulation from last week and the results at least on a macro scale did not change much 


### Task 3: Boundary conditions

1. **Outflow Boundaries**
   - The outflow boundaries were pretty quick to implement
   - Since we have to update the cells and their particle lists anyway, we check the halo cells after every loop
and delete all particles that they hold
2. **Reflective Boundaries**
   - The reflective boundaries were a bit more tricky
   - We figured that the idea to create and save a new halo ghost particle for every 
particle too close to the boundary would be too memory inefficient and complicated to implement 
with our code base
   - So every time a particle come too close to a boundary in our simulation, we create a hypothetical particle
that helps us calculate the force from the reflective boundary, but we do not save it 

### Task 4: Simulation of a falling drop - Wall
1. **Generate sphere**
    - The sphere spawner is basically a cube spawner that only adds those particles that have the right distance from the center

2. **Observations of the simulation**
    - The simulation should have looked like a water drop thrown at a surface in space and that is looks like
    - The sphere is deformed at first and then gives this "Deformation Energy" back and scattering in all direction with 
high velocity
    - All of this seems very physically realistic to us so we were very happy with the results :)
### Misc

- During this sheet we found a way to incorporate ray tracing in paraview making 3-D Simulations prettier and easier to follow 
- This was important to us during these tasks to check the validity of our simulations in all dimensions and with all boundary conditions
