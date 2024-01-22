#include "Cell.h"

Cell::Cell(CellType cell_type) : cell_type(cell_type) { neighbour_references.reserve(26); }

Cell::CellType Cell::getCellType() const { return cell_type; }

std::vector<Particle*>& Cell::getParticleReferences() { return particle_references; }

std::vector<Cell*>& Cell::getNeighbourReferences() { return neighbour_references; }

void Cell::addParticleReference(Particle* p) { particle_references.push_back(p); }

void Cell::clearParticleReferences() { particle_references.clear(); }

void Cell::addNeighbourReference(Cell* c) { neighbour_references.push_back(c); }
