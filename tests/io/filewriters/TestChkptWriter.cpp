#include <gtest/gtest.h>

#include "data/FileLoader.h"
#include "io/input/FileInputHandler.h"
#include "io/output/FileOutputHandler.h"
#include "particles/containers/directsum/DirectSumContainer.h"

/*
 * Test if the CheckPointWriter can write a file that can be read by the CheckPointReader without errors.
 */
TEST(CHKPTWriter, CorrectWritingAndReadingOfParticles) {
    std::unique_ptr<ParticleContainer> particle_container = std::make_unique<DirectSumContainer>();

    for (double i = 1; i < 5; i++) {
        auto pos = std::array<double, 3>{i, 2 * i, 3 * i};
        auto vel = std::array<double, 3>{4 * i, 5 * i, 6 * i};
        bool is_odd = (int)i % 2 == 1;
        Particle particle(pos, vel, i, i, i * i, i * i * i, is_odd ? LockState::LOCKED : LockState::UNLOCKED);
        particle.addConnectedParticle(i, i + 0.25, i + 0.5);
        particle_container->addParticle(particle);
    }

    auto params = SimulationParams("test.xml", 0, 0, SimulationParams::DirectSumType{}, {}, {}, {}, {}, false);

    FileOutputHandler file_output_handler{OutputFormat::CHKPT, params};

    auto path = file_output_handler.writeFile(0, particle_container);

    // load the file
    ChkptPointFileReader reader;

    auto [loaded_particles, loaded_config] = reader.readFile(*path);

    // check if the file contains the correct data
    EXPECT_EQ(loaded_particles.size(), particle_container->size());

    for (size_t i = 0; i < loaded_particles.size(); i++) {
        EXPECT_EQ(loaded_particles.at(i), particle_container->getParticles().at(i));

        for (size_t j = 0; j < loaded_particles.at(i).getConnectedParticles().size(); j++) {
            EXPECT_EQ(loaded_particles.at(i).getConnectedParticles().at(j),
                      particle_container->getParticles().at(i).getConnectedParticles().at(j));
        }
    }
}