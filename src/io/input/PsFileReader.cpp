/**
 * PsFileReader.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "PsFileReader.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

void PsFileReader::readFile(const std::string& filepath, ParticleContainer& particle_container) {
    std::array<double, 3> x;
    std::array<double, 3> v;
    double m;
    int num_particles = 0;

    std::ifstream input_file(filepath);
    std::string tmp_string;

    if (input_file.is_open()) {
        getline(input_file, tmp_string);

        while (tmp_string.empty() or tmp_string[0] == '#') {
            getline(input_file, tmp_string);
        }

        std::istringstream numstream(tmp_string);
        numstream >> num_particles;
        particle_container.reserve(num_particles);
        getline(input_file, tmp_string);

        for (int i = 0; i < num_particles; i++) {
            std::istringstream datastream(tmp_string);

            for (auto& xj : x) {
                datastream >> xj;
            }
            for (auto& vj : v) {
                datastream >> vj;
            }
            if (datastream.eof()) {
                std::cout << "Error reading file: eof reached unexpectedly reading from line " << i << std::endl;
                exit(-1);
            }
            datastream >> m;

            particle_container.addParticle(Particle{x, v, m, i});

            getline(input_file, tmp_string);
        }
    } else {
        std::cout << "Error: could not open file " << filepath << std::endl;
        exit(-1);
    }
}