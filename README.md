# MolSim

[![Build Project](https://github.com/ManuelLerchner/MolSim-WS23-24/actions/workflows/build-project.yml/badge.svg)](https://github.com/ManuelLerchner/MolSim-WS23-24/actions/workflows/build-project.yml)
[![Build Docs](https://github.com/ManuelLerchner/MolSim-WS23-24/actions/workflows/build-docs.yml/badge.svg)](https://github.com/ManuelLerchner/MolSim-WS23-24/actions/workflows/build-docs.yml)

Code for the practical course PSE: Molecular Dynamics by group C (WS 2023/24).

**Group members:**

- Manuel Lerchner
- Tobias Eppacher
- Daniel Safyan

## Tools

### Build tools and versions

- Tested with `gcc 13.1.0`
- Tested with `CMake 3.28.0`
- Tested with `make 4.3`

### Dependencies

- Doxygen 1.10.0: (optional, only needed for documentation)
  - Graphviz: `sudo apt install graphviz` (optional, only needed for drawing UML diagrams in doxygen)
- Libxerces: `sudo apt install libxerces-c-dev`
- Boost Program Options: `sudo apt-get install libboost-program-options-dev`

## Build

### Without Doxygen

1. Create and enter into the build directory: `mkdir -p build && cd build`
2. Run cmake: `cmake ..` to configure the project.
3. Run `make` to build the program.

### With Doxygen

1. Create and enter into the build directory: `mkdir -p build && cd build`
2. Run cmake: `cmake .. -D BUILD_DOC_DOXYGEN=ON` to configure the project.
3. Run `make` to build the program. Run `make doc_doxygen` to build the documentation.

## Run

- Run `./MolSim <FILENAME>` to run the program. `<FILENAME>` is the path to the input file.

### Optional Parameters

- Execute `./MolSim --help` to get a detailed list of all options, parameters and their default values.
