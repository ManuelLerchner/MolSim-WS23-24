#include "VTUWriter.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

VTKFile_t VTUWriter::initializeOutput(int numParticles) {
    VTKFile_t vtuFile("UnstructuredGrid");

    // per point, we add type, position, velocity and force
    PointData pointData;
    DataArray_t mass(type::Float32, "mass", 1);
    DataArray_t velocity(type::Float32, "velocity", 3);
    DataArray_t forces(type::Float32, "force", 3);
    DataArray_t type(type::Int32, "type", 1);
    pointData.DataArray().push_back(mass);
    pointData.DataArray().push_back(velocity);
    pointData.DataArray().push_back(forces);
    pointData.DataArray().push_back(type);

    CellData cellData;  // we don't have cell data => leave it empty

    // 3 coordinates
    Points points;
    DataArray_t pointCoordinates(type::Float32, "points", 3);
    points.DataArray().push_back(pointCoordinates);

    Cells cells;  // we don't have cells, => leave it empty
    // for some reasons, we have to add a dummy entry for paraview
    DataArray_t cells_data(type::Float32, "types", 0);
    cells.DataArray().push_back(cells_data);

    PieceUnstructuredGrid_t piece(pointData, cellData, points, cells, numParticles, 0);
    UnstructuredGrid_t unstructuredGrid(piece);
    vtuFile.UnstructuredGrid(unstructuredGrid);

    return vtuFile;
}

void VTUWriter::plotParticle(VTKFile_t& vtuFile, const Particle& p) {
    PointData::DataArray_sequence& pointDataSequence = vtuFile.UnstructuredGrid()->Piece().PointData().DataArray();
    PointData::DataArray_iterator dataIterator = pointDataSequence.begin();

    dataIterator->push_back(p.getM());

    dataIterator++;
    dataIterator->push_back(p.getV()[0]);
    dataIterator->push_back(p.getV()[1]);
    dataIterator->push_back(p.getV()[2]);

    dataIterator++;
    dataIterator->push_back(p.getOldF()[0]);
    dataIterator->push_back(p.getOldF()[1]);
    dataIterator->push_back(p.getOldF()[2]);

    dataIterator++;
    dataIterator->push_back(p.getType());

    Points::DataArray_sequence& pointsSequence = vtuFile.UnstructuredGrid()->Piece().Points().DataArray();
    Points::DataArray_iterator pointsIterator = pointsSequence.begin();
    pointsIterator->push_back(p.getX()[0]);
    pointsIterator->push_back(p.getX()[1]);
    pointsIterator->push_back(p.getX()[2]);
}

void VTUWriter::writeFile(const SimulationParams& params, size_t iteration,
                          const std::unique_ptr<ParticleContainer>& particle_container) const {
    auto filename = params.output_dir_path + "/" + "MD_VTU";

    std::stringstream strstr;
    strstr << filename << "_" << std::setfill('0') << std::setw(4) << iteration << ".vtu";

    auto vtuFile = initializeOutput(static_cast<int>(particle_container->size()));

    for (const Particle& particle : *particle_container) {
        plotParticle(vtuFile, particle);
    }

    std::ofstream file(strstr.str().c_str());
    VTKFile(file, vtuFile);
    file.close();
}
