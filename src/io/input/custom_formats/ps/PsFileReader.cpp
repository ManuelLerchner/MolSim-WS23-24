#include "PsFileReader.h"

#include <spdlog/fmt/bundled/core.h>

#include <fstream>
#include <sstream>

std::tuple<std::vector<Particle>, std::optional<SimulationParams>> PsFileReader::readFile(const std::filesystem::path& filepath) const {
    std::array<double, 3> x{};
    std::array<double, 3> v{};
    double m;
    int num_particles = 0;

    std::ifstream input_file(filepath);
    std::string curr_line;

    if (!input_file.is_open()) {
        throw FileFormatException(fmt::format("Error: could not open file '{}'.", filepath.string()));
    }

    getline(input_file, curr_line);

    while (curr_line.empty() or curr_line[0] == '#') {
        getline(input_file, curr_line);
    }

    // Initialize particle container
    std::vector<Particle> particles;

    std::istringstream numstream(curr_line);
    numstream >> num_particles;
    getline(input_file, curr_line);

    for (int i = 0; i < num_particles; i++) {
        std::istringstream datastream(curr_line);

        for (auto& xj : x) {
            datastream >> xj;
        }
        for (auto& vj : v) {
            datastream >> vj;
        }
        if (datastream.eof()) {
            throw FileFormatException(fmt::format("Error reading file: eof reached unexpectedly reading from line {}.", i));
        }
        datastream >> m;

        particles.emplace_back(x, v, m, i);

        getline(input_file, curr_line);
    }

    return std::make_tuple(particles, std::nullopt);
}
