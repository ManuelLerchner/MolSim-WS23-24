<!-- markdownlint-disable-next-line -->
@~english
\page InputFileFormats Input File Formats

## Overview

Our program supports multiple file formats as input files, which are interpreted differently. The file format is automatically determined by the file extension.
The following file extensions are supported:

- `.xml`: Contains data for particle generation and allows to specify all the input parameters for the simulation as well

In the following sections, the file formats are explained in detail.

## File Formats Explained

### .xml

The `.xml` file format can be used to specify all the input parameters for the simulation at once. Therefore, it is preferred over the other file formats.

Its definition is based on the [simulation_schema.xsd](simulation_schema.xsd) file, which is used to validate the input file. The file contains a single root element `<configuration>` and can contain the following elements:

- Settings:
  - `<delta_t>`: The time step size
  - `<end_time>`: The time at which the simulation should end
  - `<particle_container>` Which particle container implementation should be used

- Forces:
  - `<LennardJones>`: The Lennard-Jones force
  - `<Harmonic>`: The harmonic force used between linked particles
  - `<Gravity>`: The gravity force between particles
  - `<GlobalGravity>`: The gravity force acting on all particles
  - ...

- Interceptors:
  - `<FrameWriter>`: Writes the simulation state to a file at a specified frame rate
  - `<ParticleUpdateCounter>`: Counts the number of particle updates
  - `<RadialDistributionFunction>`: Calculates the radial distribution function of the particles
  - `<Thermostats>`: Applies a thermostat to the particles
  - ...
  
- Particle Data:
  - `<cuboid_spawner>`: Input data for a cuboid spawner, which generates particles in a cuboid shape (2 or 3 dimensional)
  - `<sphere_spawner>`: Input data for a sphere spawner, which generates particles in a spherical shape (2 or 3 dimensional)
  - `<single_particle_spawner>`: Input data for a single particle, which is placed at the specified position
  - `<subsimulations>`: Input data for a subsimulation, which is run recursively and then copied into the main simulation
  - ...

An example file could look like this:

```xml
<?xml version="1.0"?>
<configuration xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:noNamespaceSchemaLocation="../simulation_schema.xsd">

    <settings>
        <delta_t>0.0005</delta_t>
        <end_time>20.0</end_time>
        <third_dimension>false</third_dimension>
        <particle_container>
            <linkedcells_container>
                <domain_size>
                    <x>180</x>
                    <y>90</y>
                    <z>3</z>
                </domain_size>
                <cutoff_radius>3.0</cutoff_radius>
                <boundary_conditions>
                    <left>Outflow</left>
                    <right>Outflow</right>
                    <bottom>Outflow</bottom>
                    <top>Outflow</top>
                    <back>Outflow</back>
                    <front>Outflow</front>
                </boundary_conditions>
            </linkedcells_container>
        </particle_container>
        <forces>
            <LennardJones />
        </forces>
        <interceptors>
            <FrameWriter output_format="vtu" fps="24" video_length_s="30" />
        </interceptors>
    </settings>

    <particle_source>
        <cuboid_spawner>
            <lower_left_front_corner>
                <x>20.0</x>
                <y>20.0</y>
                <z>1.5</z>
            </lower_left_front_corner>
            <grid_dim>
                <x>100</x>
                <y>20</y>
                <z>1</z>
            </grid_dim>
            <grid_spacing>1.1225</grid_spacing>
            <temperature>0.1</temperature>
            <mass>1</mass>
            <velocity>
                <x>0.0</x>
                <y>0.0</y>
                <z>0.0</z>
            </velocity>
            <type>0</type>
            <epsilon>1.0</epsilon>
            <sigma>1.2</sigma>
        </cuboid_spawner>
    </particle_source>

</configuration>
```
