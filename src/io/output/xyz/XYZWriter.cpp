#include "XYZWriter.h"

#include <iomanip>
#include <sstream>

const std::string XYZWriter::writeFile(const SimulationParams& params, size_t iteration, const std::vector<Particle>& particles) const {
    auto file_base = params.output_dir_path + "/" + "MD_XYZ";

    std::stringstream strstr;
    strstr << file_base << "_" << std::setfill('0') << std::setw(4) << iteration << ".xyz";

    std::ofstream file;

    auto file_name = strstr.str();

    file.open(strstr.str().c_str());
    file << particles.size() << std::endl;
    file << "Generated by MolSim. See http://openbabel.org/wiki/XYZ_(format) for file format doku." << std::endl;

    for (auto& p : particles) {
        std::array<double, 3> x = p.getX();
        file << "Ar ";
        file.setf(std::ios_base::showpoint);

        for (auto& xi : x) {
            file << xi << " ";
        }

        file << std::endl;
    }

    file.close();

    return file_name;
}
